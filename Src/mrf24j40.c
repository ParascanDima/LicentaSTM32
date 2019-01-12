/*
 * mrf24j40.c
 *
 *  Created on: 27 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "mrf24j40.h"
#include "mrf24j40if.h"
#include "mrf24j40_memmap.h"
#include <string.h>         // memset()

/**************Private Macro Definitions*****************/


#define bite_32(x)  ((uint32_t*)&(x))

#define MAX_RX_PAYLOAD_SIZE       (RX_FIFO_MEM_SIZE-FRAME_LENGTH_BYTES - FRAME_CONTROL_BYTES - SEQUENCE_NUMBER_BYTES - MAX_DST_PANID_BYTES -\
                                   MAX_DST_ADDR_BYTES - MAX_SRC_PANID_BYTES - MAX_SRC_ADDR_BYTES - MAX_AUX_SECURITY_HEADER_BYTES)

#define RX_FRAME_LENGTH_VALUE_ADDR       RX_FIFO_START_ADDR
#define RX_FRAME_CONTROL_VALUE_ADDR      RX_FRAME_LENGTH_VALUE_ADDR + ONE_BYTE
#define RX_SEQUENCE_NUMBER_VALUE_ADDR    RX_FRAME_CONTROL_VALUE_ADDR + TWO_BYTES
#define RX_ADDRESSING_FIELD_START_ADDR   RX_SEQUENCE_NUMBER_VALUE_ADDR + ONE_BYTE

#define CHANNEL_BUSY          CCAFAIL
#define CHANNEL_IDLE          (0x00)

#define RSH(x)                >> x

#define MRF24J40_COPY_BYTES_TO(variable, n, fromAddress)   for(index = 0; index < n; ++index){ \
        BYTEPTR(variable)[index] = highRead(fromAddress+index); \
}

/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/

uint8_t txPayload[TX_PAYLOAD_SIZE];     // TX payload buffer
uint8_t rxPayload[MAX_RX_PAYLOAD_SIZE]; // RX payload buffer

/**************Public Variable Definitions***************/

MRF24J40_STATUS volatile RadioStatus; // radio state
PACKET Tx, Rx; // structures describing transmitted and received packets
ZigBeeStateType mrf24j40State = ZIGBEE_UNINITIALIZED;

/**************Private Function Definitions**************/


/* The key to understanding SPI is that there is only 1 clock line, and so all transfers
   are always bidirectional - you send one bit for each you receive and vice-versa.  And the CLK
   only runs (in Master mode) when you transmit.

   So to transmit, you store to the TX buffer, wait for it to clock out, flush away the bogus received byte.

   And to receive, you send, wait for the byte to clock in, then read it.

 */


uint8_t highRead(uint16_t address) {
    uint8_t toReturn;

    MRF24J40_ChipSelectPullDown();

    MRF24J40IF_SpiTransmit(((address >> 3)&0x7F) | 0x80);
    MRF24J40IF_SpiTransmit(((address << 5)&0xE0));
    toReturn = MRF24J40IF_SpiReceive();

    MRF24J40_ChipSelectPullUp();
    return toReturn;
}


// writes "value" to radio at long "address"

void highWrite(uint16_t address, uint8_t value) {

    MRF24J40_ChipSelectPullDown();

    MRF24J40IF_SpiTransmit((((uint8_t) (address >> 3))&0x7F) | 0x80);
    MRF24J40IF_SpiTransmit((((uint8_t) (address << 5))&0xE0) | 0x10);
    MRF24J40IF_SpiTransmit(value);

    MRF24J40_ChipSelectPullUp();

}

// reads byte from radio at short "address"

uint8_t lowRead(uint8_t address) {
    uint8_t toReturn;

    MRF24J40_ChipSelectPullDown();

    MRF24J40IF_SpiTransmit((address<<1)&0xFE);
    toReturn = MRF24J40IF_SpiReceive();

    MRF24J40_ChipSelectPullUp();


    return toReturn;
}

// writes "value" to radio at short "address"

void lowWrite(uint8_t address, uint8_t value) {

    MRF24J40_ChipSelectPullDown();

    MRF24J40IF_SpiTransmit((address<<1)|0x01);
    MRF24J40IF_SpiTransmit(value);

    MRF24J40_ChipSelectPullUp();

}

// reads byte from radio at long "address"

uint8_t ReadRegister(uint16_t reg){
    uint8_t regValue = 0;

    if(reg < HIGH_CONTROL_REGISTERS_START_ADDR){

        regValue = lowRead((uint8_t)reg);

    }
    else{

        regValue = highRead(reg);

    }

    return regValue;
}


void WriteRegister(uint16_t reg, uint8_t value){

    if(reg < HIGH_CONTROL_REGISTERS_START_ADDR){

        lowWrite((uint8_t)reg, value);
    }
    else{

        highWrite(reg, value);
    }
}


uint16_t WriteMemory(uint8_t section, uint8_t offset, uint8_t* source, uint8_t nrOfBytes){
    uint16_t rsp;
    MemorySection sector = GetSectionById(section);
    uint16_t addr = sector.startAddr + (uint16_t)offset;

    if (sector.isWritable && !sector.isRegisterSection)
    {
        if(addr <= sector.endAddr)
        {
            if((sector.endAddr - addr) > nrOfBytes)
            {

                while (nrOfBytes--)
                {
                    highWrite(addr++, *source++);
                }

                rsp = addr;
            }
            else
            {
                rsp = sector.endAddr;
            }
        }
        else
        {
            rsp = sector.endAddr;
        }
    }
    else{
        sector = GetSectionById(TX_NORMAL_FIFO_SECTION);
        rsp = sector.endAddr;
    }

    return rsp;
}

uint8_t ReadMemory(uint8_t section, uint8_t offset, uint8_t* source, uint8_t nrOfBytes){

    MemorySection sector = GetSectionById(section);
    uint16_t addr = sector.startAddr + (uint16_t)offset;
    uint16_t rsp = sector.endAddr;

    if (sector.isWritable && !sector.isRegisterSection)
    {
        if(addr <= sector.endAddr)
        {
            if((sector.endAddr - addr) > nrOfBytes)
            {

                while (nrOfBytes--)
                {
                    *source++ = highRead(addr++);
                }

                rsp = addr;
            }
            else
            {

            }
        }
        else
        {

        }
    }

    return rsp;
}


void ParseReceivedMessage(void){

    uint8_t index = 0;
    uint16_t dstPANIDAddr = 0;
    uint16_t dstAddrValueAddr = 0;
    uint16_t srcPANIDAddr = 0;
    uint16_t srcAddrValueAddr = 0;
    uint16_t auxSecHeaderAddr = 0;
    uint16_t payloadAddr = 0;

    Rx.payloadLength = 0;

    MRF24J40_COPY_BYTES_TO(Rx.frameLength, ONE_BYTE, RX_FRAME_LENGTH_VALUE_ADDR);  // Frame length byte shows the length of packet except LQI and RSSI bytes
    MRF24J40_COPY_BYTES_TO(Rx.frameControl.value, TWO_BYTES, RX_FRAME_CONTROL_VALUE_ADDR);
    MRF24J40_COPY_BYTES_TO(Rx.frameNumber, ONE_BYTE, RX_SEQUENCE_NUMBER_VALUE_ADDR);

    if(Rx.frameControl.Field.dstAddrMode != NO_ADDR_FIELD){

        dstPANIDAddr = RX_SEQUENCE_NUMBER_VALUE_ADDR + ONE_BYTE;
        MRF24J40_COPY_BYTES_TO(Rx.dstPANID, TWO_BYTES, dstPANIDAddr);

        dstAddrValueAddr = dstPANIDAddr + TWO_BYTES;

        switch (Rx.frameControl.Field.dstAddrMode)
        {
            case SHORT_ADDR_FIELD:
                MRF24J40_COPY_BYTES_TO(Rx.dstAddr, TWO_BYTES, dstAddrValueAddr);
                srcPANIDAddr = dstAddrValueAddr + TWO_BYTES;
                break;

            case LONG_ADDR_FIELD:
                MRF24J40_COPY_BYTES_TO(Rx.dstAddr, EIGHT_BYTES, dstAddrValueAddr);
                srcPANIDAddr = dstAddrValueAddr + EIGHT_BYTES;
                break;

            default:
                return;
        }
    }
    else{
        srcPANIDAddr = RX_SEQUENCE_NUMBER_VALUE_ADDR + ONE_BYTE;
    }

    if(Rx.frameControl.Field.srcAddrMode != NO_ADDR_FIELD){

        if(Rx.frameControl.Field.panIDcomp == 0){
            MRF24J40_COPY_BYTES_TO(Rx.srcPANID, TWO_BYTES, srcPANIDAddr);
            srcAddrValueAddr = srcPANIDAddr + TWO_BYTES;
        }
        else{
            Rx.srcPANID = Rx.dstPANID;
            srcAddrValueAddr = srcPANIDAddr;
        }


        switch (Rx.frameControl.Field.dstAddrMode)
        {
            case SHORT_ADDR_FIELD:
                MRF24J40_COPY_BYTES_TO(Rx.srcAddr, TWO_BYTES, srcAddrValueAddr);
                auxSecHeaderAddr = srcAddrValueAddr + TWO_BYTES;
                break;

            case LONG_ADDR_FIELD:
                MRF24J40_COPY_BYTES_TO(Rx.srcAddr, EIGHT_BYTES, srcAddrValueAddr);
                auxSecHeaderAddr = srcAddrValueAddr + EIGHT_BYTES;
                break;

            default:
                return;
        }
    }
    else{
        auxSecHeaderAddr = srcPANIDAddr;
    }

    if(Rx.frameControl.Field.securityEnabled){

        MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.securityControl.value, ONE_BYTE, auxSecHeaderAddr);
        MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.frameCounter, FOUR_BYTES, auxSecHeaderAddr+ONE_BYTE);

        auxSecHeaderAddr += (FOUR_BYTES + ONE_BYTE);

        if(Rx.auxSecurityHeader.securityControl.Field.keyIdMode != KEY_ID_MODE_IMPLICIT){

            switch (Rx.auxSecurityHeader.securityControl.Field.keyIdMode)
            {
                case KEY_ID_MODE_1BYTE:
                    MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.keyID.keyIndex, ONE_BYTE, auxSecHeaderAddr);
                    payloadAddr = auxSecHeaderAddr + ONE_BYTE;
                break;


                case KEY_ID_MODE_4BYTE:

                    MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.keyID.keySource, FOUR_BYTES, auxSecHeaderAddr);
                    MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.keyID.keyIndex, ONE_BYTE, auxSecHeaderAddr+FOUR_BYTES);
                    payloadAddr = auxSecHeaderAddr + (FOUR_BYTES+ONE_BYTE);
                break;


                case KEY_ID_MODE_8BYTE:

                    MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.keyID.keySource, EIGHT_BYTES, auxSecHeaderAddr);
                    MRF24J40_COPY_BYTES_TO(Rx.auxSecurityHeader.keyID.keyIndex, ONE_BYTE, auxSecHeaderAddr+EIGHT_BYTES);
                    payloadAddr = auxSecHeaderAddr + (EIGHT_BYTES+ONE_BYTE);
                break;
            }

        }
    }
    else{
        payloadAddr = auxSecHeaderAddr;
    }

    Rx.headerLength = payloadAddr - RX_FIFO_START_ADDR;


    for (index = 0; index < (Rx.frameLength-1)-Rx.headerLength; ++index)
    {
        Rx.payload[Rx.payloadLength++] = highRead(payloadAddr+index);
    }

    MRF24J40_COPY_BYTES_TO(Rx.fcs, TWO_BYTES, payloadAddr+Rx.payloadLength);
    MRF24J40_COPY_BYTES_TO(Rx.lqi, ONE_BYTE, payloadAddr+Rx.payloadLength+TWO_BYTES);
    MRF24J40_COPY_BYTES_TO(Rx.rssi, ONE_BYTE, payloadAddr+Rx.payloadLength+TWO_BYTES+ONE_BYTE);
}


// writes count consecutive bytes from source into consecutive FIFO slots starting at "register".  Returns next empty register #.

uint8_t toTXfifo(uint16_t reg, uint8_t* source, uint8_t count) {

    while (count--){
        highWrite(reg++, *source++);
    }

    return reg;
}




/**************Public Function Definitions***************/

ZigBeeStateType MRF24J40_GetState(void)
{
	return mrf24j40State;
}




// warm start radio hardware, tunes to Channel.  Takes about 0.37 ms on PIC32 at 20 MHz, 10 MHz SPI hardware clock
// on return, 0=no radio hardare, 1=radio is reset

uint8_t initMRF24J40(void) {
    uint8_t i = 0;
    uint32_t radioReset = MRF24J40IF_GetSysMilliseconds(); // record time we started the reset procedure

    MRF24J40_PinOutInit();

    MRF24J40IF_Delay_ms(2);

    RadioStatus.LastTXTriggerTick=0;
    RadioStatus.ResetCount++;

    RadioStatus.TX_BUSY = 0; // tx is not busy after reset

    if(RadioStatus.ResetCount != START_UP){

        RadioStatus.TX_FAIL = 1; // if we had to reset, consider last packet (if any) as failed
    }
    RadioStatus.TX_PENDING_ACK = 0; // not pending an ack after reset
    RadioStatus.SLEEPING = 0; // radio is not sleeping

    /* do a soft reset */
    lowWrite(SOFTRST, RSTPWR|RSTBB|RSTMAC); // reset everything (power, baseband, MAC) (also does wakeup if in sleep)
    do {
        i = lowRead(SOFTRST);

        if (MRF24J40IF_ElapsedTimeSince(radioReset) > MILLISECONDS(50)) // if no reset in a reasonable time
            return 0; // then there is no radio hardware
    } while ((i & (RSTPWR|RSTBB|RSTMAC)) != (uint8_t)CLEAR_REGISTER); // wait for hardware to clear reset bits
    lowWrite(RXFLUSH, RXFLUSH_BIT); //RXFLUSH = 0x01 flush the RX fifo, leave WAKE pin disabled

    RadioSetAddress(RadioStatus.MyShortAddress, RadioStatus.MyLongAddress, RadioStatus.MyPANID);

    highWrite(RFCON0, RFOPT_1|RFOPT_0); // RFOPT=0x03
    highWrite(RFCON1, VCOOPT_1); // VCOOPT=0x02, per datasheet
    highWrite(RFCON2, PLLEN); // RFCON2 = 0x80 PLL enable
    highWrite(RFCON3, TX_POWER); // RFCON3 = 0x00 set transmit power
    highWrite(RFCON6, TXFIL|_20MRECVR); // RFCON6 = 0x90 TXFILter on, 20MRECVR set to < 3 mS
    highWrite(RFCON7, SLPCLKSEL_1); // RFCON7 = 0x80 sleep clock 100 kHz internal
    highWrite(RFCON8, RFVCO); // RFCON8 = 0x10 RFVCO to 1

    highWrite(SLPCON1, CLKOUTEN|SLPCLKDIV_0); // SLPCON1 = 0x21 CLKOUT disabled, sleep clock divisor is 2

    lowWrite(BBREG2, CCAMO); // BBREG2 = 0x80 CCA energy threshold mode
    lowWrite(CCAEDTH, CCAEDTH_6|CCAEDTH_5); // CCAEDTH = 0x60 CCA threshold ~ -69 dBm
    lowWrite(BBREG6, RSSIMODE_2); // BBREG6 = 0x40 RSSI on every packet

#if defined(ENABLE_PA_LNA)
    highWrite(TESTMODE, TESTMODE_3|TESTMODE_2|TESTMODE_1|TESTMODE_0); // TESTMODE = 0x0F setup for PA_LNA mode control
#endif
    lowWrite(PACON2, FIFOEN|TXONTS2|TXONTS1); // PACON2 = 0x98, per datasheet init
    lowWrite(TXSTBL, RFSTBL_3|RFSTBL_0|MSIFS_2|MSIFS_0); // TXSTBL = 0x95; RFSTBL=9, MSIFS-5
    while ((highRead(RFSTATE)&(RFSTATE_2|RFSTATE_0)) != (RFSTATE_2|RFSTATE_0)); // wait till RF state machine in RX mode

    lowWrite(INTCON, (uint8_t)(~(RXIE|TXNIE))); // INTCON = 0xF6, enabled=0. RXIE and TXNIE only enabled.

    // Make RF communication stable under extreme temperatures
    highWrite(RFCON0, RFOPT_1|RFOPT_0); // RFCON0 = 0x03 this was previously done above
    highWrite(RFCON1, VCOOPT_1); // RFCON1 = 0x02 VCCOPT - whatever that does...

    RadioSetChannel(RadioStatus.Channel); // tune to current radio channel

#ifdef TURBO_MODE           // propriatary TURBO_MODE runs at 625 kbps (vs. 802.15.4 compliant 250 kbps)
    lowWrite(BBREG0, TURBO);    // BBREG0 = 0x01 TURBO mode enable
    lowWrite(BBREG3, CCACSTH_3|CCACSTH_2|CCACSTH_1);    // BBREG3 = 0x38 PREVALIDTH to turbo optimized setting
    lowWrite(BBREG4, CSTH_1|PRECNT_2|PRECNT_1|PRECNT_0);    // BBREG4 = 0x5C CSTH carrier sense threshold to turbo optimal
#endif

    lowWrite(RFCTL, RFRST); // RFCTL = 0x04 reset RF state machine
    lowWrite(RFCTL, CLEAR_REGISTER); // RFCTL = 0x00 back to normal operation

    // now delay at least 192 uS per datasheet init
    MRF24J40IF_Delay_ms(10);

    MRF24J40_InterruptEnable();
    mrf24j40State = ZIGBEE_INITIALIZED;
    return 1;
}

// on return, 1=radio is setup, 0=there is no radio

uint8_t RadioInit(void) // cold start radio init
{
    uint8_t radio;

    memset((void*) &RadioStatus, 0, sizeof (RadioStatus));

    RadioStatus.MyPANID = MY_PAN_ID;

    RadioStatus.MyShortAddress = SERVER_SHORT_ADDRESS;

    RadioStatus.ServerShortAddress = SERVER_SHORT_ADDRESS;
    RadioStatus.MyLongAddress = SERVER_SHORT_ADDRESS;
    RadioStatus.Channel = 11; // start at channel 11
    Rx.payload = rxPayload;
    Tx.payload = txPayload;

    radio = initMRF24J40(); // init radio hardware, tune to RadioStatus.Channel


    return radio;
}

// set short address and PANID

void RadioSetAddress(uint16_t shortAddress, uint64_t longAddress, uint16_t panID) {
    uint8_t i;

    lowWrite(SADRL, BYTEPTR(shortAddress)[0]);
    lowWrite(SADRH, BYTEPTR(shortAddress)[1]);

    lowWrite(PANIDL, BYTEPTR(panID)[0]);
    lowWrite(PANIDH, BYTEPTR(panID)[1]);

    for(i=0;i<sizeof(longAddress);i++){ // program long MAC address
        lowWrite(EADR0+i,BYTEPTR(longAddress)[i]);
    }

    RadioStatus.MyPANID = panID;
    RadioStatus.MyShortAddress = shortAddress;
    RadioStatus.MyLongAddress = longAddress;
}

// Set radio channel.  Returns with success/fail flag.

uint8_t RadioSetChannel(uint8_t channel) {
    if (channel < 11 || channel > 26)
        return EXIT_FAILURE;

#if defined(ENABLE_PA_LNA)  // Permitted band is 2400 to 2483.5 MHz.
    if (channel == 26) // Center Freq. is 2405+5(k-11) MHz, for k=channel 11 to 26
        return EXIT_FAILURE; // max output is 100mW (USA)
#endif                      // rolloff is not steep enough to avoid 2483.5 from channel 26 center of 2480 MHz at full MB power

    RadioStatus.Channel = channel;
    highWrite(RFCON0, ((channel - 11) << 4) | 0x03);
    lowWrite(RFCTL, RFRST); // reset RF state machine
    lowWrite(RFCTL, CLEAR_REGISTER); // back to normal

    return EXIT_SUCCESS;
}

// Put the RF transceiver into sleep or wake it up
// Radio power, MRF24J40MB - ENABLE_PA_LNA on:
//  RX:     28.4 mA
//  TX:     65.8 mA (as fast as I can xmit; nominal peak 130 mA)
//  Sleep:  0.245 mA (spec is 5 uA with 'sleep clock disabled'; setting register 0x211 to 0x01 doesn't seem to help)
// Note that you can in practice turn the radio power off completely for short periods (with a MOSFET) and then do a warm start.

void RadioSetSleep(uint8_t powerState) {
    if (powerState) {
#if defined(ENABLE_PA_LNA)
        highWrite(TESTMODE, TESTMODE_3); // TESTMODE = 0x08 Disable automatic switch on PA/LNA
        lowWrite(TRISGPIO, TRISGP_3|TRISGP_2|TRISGP_1|TRISGP_0); // TRISGPIO = 0x0F Set GPIO direction to OUTPUT (control PA/LNA)
        lowWrite(GPIO, CLEAR_REGISTER); // GPIO = 0x00 Disable PA and LNA
#endif

        lowWrite(SOFTRST, RSTPWR); // SOFTRST = 0x04 power management reset to ensure device goes to sleep
        lowWrite(WAKECON, IMMWAKE); // WAKECON = 0x80 WAKECON; enable immediate wakeup
        lowWrite(SLPACK, SLPACK_BIT); // SLPACK = 0x80 SLPACK; force radio to sleep now

        RadioStatus.SLEEPING = 1; // radio is sleeping
    }
    else
        initMRF24J40(); // could wakeup with WAKE pin or by toggling REGWAKE (1 then 0), but this is simpler
}

// Do a single (128 us) energy scan on current channel.  Return RSSI.

uint8_t RadioEnergyDetect(void) {
    uint8_t RSSIcheck;

#if defined(ENABLE_PA_LNA)
    highWrite(TESTMODE, TESTMODE_3); // TESTMODE = 0x08 Disable automatic switch on PA/LNA
    lowWrite(TRISGPIO, TRISGP_3|TRISGP_2|TRISGP_1|TRISGP_0); // TRISGPIO = 0x0F Set GPIO direction to OUTPUT (control PA/LNA)
    lowWrite(GPIO, GPIO_3|GPIO_2); // GPIO = 0x0C Enable LNA, disable PA
#endif

    lowWrite(BBREG6, RSSIMODE_1); // BBREG6 = 0x80 set RSSIMODE1 to initiate RSSI measurement

    RSSIcheck = lowRead(BBREG6); // Read RSSIRDY
    while ((RSSIcheck & RSSIRDY) != RSSIRDY) // Wait until RSSIRDY goes to 1; this indicates result is ready
        RSSIcheck = lowRead(BBREG6); // this takes max 8 symbol periods (16 uS each = 128 uS)

    RSSIcheck = highRead(RSSI); // read the RSSI

    lowWrite(BBREG6, RSSIMODE_2); // BBREG6 = 0x40 enable RSSI on received packets again after energy scan is finished

#if defined(ENABLE_PA_LNA)
    lowWrite(GPIO, CLEAR_REGISTER); // GPIO = 0x00
    lowWrite(TRISGPIO, CLEAR_REGISTER); // TRISGPIO = 0x00 Set GPIO direction to INPUT
    highWrite(TESTMODE, TESTMODE_3|TESTMODE_2|TESTMODE_1|TESTMODE_0); // TESTMODE = 0x0F setup for automatic PA/LNA control
#endif

    return RSSIcheck;
}

// TX side - what goes in the TX FIFO (MRF24J40 datahseet figure 3-11):
//
// Size Offset  Descr
// 1        0       Header length (m)
// 1        1       Frame length (m+n)
// 1        2       LSB of Frame Control (bits/i)
// 1        3       MSB of Frame Control (type)
// 1        4       Sequence number
// 20       24      Addressing fields, worst case (PANIDx2 = 4, LONGx2=16 total =20)
// 103      127     Payload (from TxBuffer)

// sends raw packet per already setup Tx structure.  No error checking here.

void RadioTXRaw(void) {
    uint8_t wReg; // radio write register (into TX FIFO starting at long addr 0)
    uint8_t length = 0;

    lowWrite(TXNCON, (Tx.frameControl.value & TXNACKREQ) | INDIRECT);
    wReg = toTXfifo(TX_NORMAL_FIFO_START_ADDR+2, BYTEPTR(Tx.frameControl), 2); // frame control (2)
    wReg = toTXfifo(wReg, BYTEPTR(Tx.frameNumber), 1);                         //sequence number (1)

    if (Tx.frameControl.Field.dstAddrMode == SHORT_ADDR_FIELD) // if a short dest addr is present
    {
        wReg = toTXfifo(wReg, BYTEPTR(Tx.dstPANID), 2); // write dstPANID
        wReg = toTXfifo(wReg, BYTEPTR(Tx.dstAddr), 2); // write short address
    } else if (Tx.frameControl.Field.dstAddrMode == LONG_ADDR_FIELD)                // if a long dest addr is present
    {
        wReg = toTXfifo(wReg, BYTEPTR(Tx.dstPANID), 2); // write dstPANID
        wReg = toTXfifo(wReg, BYTEPTR(Tx.dstAddr), 8); // long addr
    }

    // now wReg is at start of source PANID (if present)

    if ( Tx.frameControl.Field.srcAddrMode != NO_ADDR_FIELD &&  // if source present
         Tx.frameControl.Field.dstAddrMode != NO_ADDR_FIELD &&  // and dest present
         !Tx.frameControl.Field.panIDcomp ){                        // and no PANID compression
        wReg = toTXfifo(wReg,BYTEPTR(Tx.srcPANID), 2);      // then write src PANID
    }

    if (Tx.frameControl.Field.srcAddrMode == SHORT_ADDR_FIELD){                 // if a short src addr is present
        wReg = toTXfifo(wReg,BYTEPTR(Tx.srcAddr), 2);
    } else if (Tx.frameControl.Field.srcAddrMode == LONG_ADDR_FIELD){                   // if a long src addr is present
        wReg = toTXfifo(wReg,BYTEPTR(Tx.srcAddr), 8);
    }

    // now wReg is pointing to first wReg after header (m)
    length = wReg-2;
    (void)toTXfifo(TX_NORMAL_FIFO_START_ADDR, BYTEPTR(length), 1);  // header length, m (-2 for header & frame lengths)

    wReg = toTXfifo(wReg, (uint8_t*)Tx.payload, Tx.payloadLength);

    length = wReg-2;
    (void)toTXfifo(TX_NORMAL_FIFO_START_ADDR+1, BYTEPTR(length), 1); // frame length (m+n)

    RadioStatus.TX_BUSY = 1;                                    // mark TX as busy TXing
    RadioStatus.TX_PENDING_ACK = Tx.frameControl.Field.ackRequest;

    lowWrite(TXNCON, TXNTRIG);// kick off transmit with above parameters
}


// Sends next packet from Tx.  Blocks for up to MRF24J40_TIMEOUT_TIME if transmitter is
// not ready (RadioStatus.TX_BUSY).  If you don't want to be blocked, don't call
// ths until RadioStatus.TX_BUSY == 0.
//
// This automatically sets frame number and source address for you
void RadioTXPacket(void){

    if(RadioWaitTXResult() == TX_RESULT_SUCCESS){
        if (Tx.frameControl.Field.srcAddrMode == SHORT_ADDR_FIELD){
            Tx.srcAddr = RadioStatus.MyShortAddress;
        } else if (Tx.frameControl.Field.srcAddrMode == LONG_ADDR_FIELD){
            Tx.srcAddr = RadioStatus.MyLongAddress;
        }

        Tx.frameNumber = RadioStatus.IEEESeqNum++;

        RadioTXRaw();
    }
}


void MRF24J40_ToSend(uint8_t* dataToSend, uint8_t length)
{
	Tx.payloadLength = length;
	memcpy(Tx.payload, dataToSend, length);
}


uint8_t MRF24J40_CheckChannelAssessment(void){

    return (lowRead(TXSTAT) & CCAFAIL);
}

// returns status of last transmitted packet: TX_SUCCESS (1), TX_FAILED (2), or 0 = no result yet because TX busy
uint8_t RadioTXResult(void) {
    if (RadioStatus.TX_BUSY) // if TX not done yet
        return TX_RESULT_BUSY;

    return TX_RESULT_SUCCESS + RadioStatus.TX_FAIL; // 1=success, 2=fail
}

// returns TX_RESULT_SUCCESS or TX_RESULT_FAILED.  Waits up to MRF24J40_TIMEOUT_TIME.

uint8_t RadioWaitTXResult(void) {

    while (RadioStatus.TX_BUSY) // If TX is busy, wait for it to clear (for a resaonable time)
        if (MRF24J40IF_ElapsedTimeSince(RadioStatus.LastTXTriggerTick) > MRF24J40_TIMEOUT_TIME){ // if not ready in a resonable time
            if(MRF24J40_CheckChannelAssessment() == CHANNEL_BUSY){
                initMRF24J40(); // reset radio hardware (stay on same channel)
            }
            else{
                RadioStatus.TX_BUSY = 0;
            }
        }

    return TX_RESULT_SUCCESS + RadioStatus.TX_FAIL; // 1=success, 2=fail
}


//  RX side - what goes in RXBuffer (from MRF24J40 datasheet figure 3-9)
//
//  Size    Offset
//  1       0       Frame length (m+n+2 = header + 102 + FCS)
//  1       1       LSB of Frame Control (bits)
//  1       2       MSB of Frame Control (type)
//  1       3       Sequence number
//  20      23      Addressing fields, worst case (PANIDx2 = 4, MACx2=16 total =20)
//  103     126     Payload
//  2       128     FCS
//  1       129     LQI
//  1       130     RSSI

// Returns count of received packets waiting to be processed & discarded.  Next packet to process is in "Rx".
// Note this gives you ALL received packets (not just ones addressed to you).   Check the addressing yourself if you care.
// Also be aware that sucessive identical packets (same frame number) will be received if the far-end misses your ACK (it
// will re-transmit).  Check for that if you care.

uint8_t RadioRXPacket(void) {

    //while (RadioStatus.TX_BUSY) // If TX is busy, wait for it to clear (for a resaonable time)
    //        if (mrf24j40_ElapsedTimeSince(RadioStatus.LastTXTriggerTick) > MRF24J40_TIMEOUT_TIME) // if not ready in a resonable time
    //            initMRF24J40(); // reset radio hardware (stay on same channel)

    return RadioStatus.RXPacketCount;
}

void RadioDiscardPacket(void) {
    if (RadioStatus.RXPacketCount) // just in case we get called more than we ought
    {
        RadioStatus.RXPacketCount--;
    } else
        RadioStatus.RadioExtraDiscard++;
}


// Interrupt handler for the MRF24J40 and P2P stack

void MRF24J40_EventHandler(void) {
    MRF24J40_InterruptDisable();

    MRF24J40_IFREG iflags;                                                          // clear IF immediately to allow next interrupt

    iflags.Val = lowRead(INTSTAT); // read ISR to see what caused the interrupt

    if (iflags.bits.RXIFG) // RX int?
    {

        lowWrite(BBREG1, RXDECINV); // set RXDECINV to disable hw RX while we're reading the FIFO

        ParseReceivedMessage();

        RadioStatus.RXPacketCount++;


        lowWrite(RXFLUSH, RXFLUSH_BIT); // flush RX hw FIFO manually (workaround for silicon errata #1)
        lowWrite(BBREG1, CLEAR_REGISTER); // reset RXDECINV to enable radio to receive next packet

        if (RadioStatus.ReceiveCallback != NULL)
        {
        	RadioStatus.ReceiveCallback();
        }
    }

    if (iflags.bits.TXIFG) // TX int?  If so, this means TX is no longer busy, and the result (if any) of the ACK request is in
    {
        RadioStatus.TX_BUSY = 0; // clear busy flag (TX is complete now)

        if (RadioStatus.TX_PENDING_ACK) // if we were waiting for an ACK
        {
            uint8_t txSTAT = lowRead(TXSTAT); // read TXSTAT, transmit status register
            RadioStatus.TX_FAIL = txSTAT & TXNSTAT; // read TXNSTAT (TX failure status)
            RadioStatus.TX_RETRIES = (txSTAT & (TXNRETRY_0|TXNRETRY_1)) RSH(BIT_6); // read TXNRETRY, number of retries of last sent packet (0..3)
            RadioStatus.TX_CCAFAIL = (txSTAT & CCAFAIL) RSH(BIT_5); // read CCAFAIL

            RadioStatus.TX_PENDING_ACK = 0; // TX finished, clear that I am pending an ACK, already got it (if I was gonna get it)
            RadioStatus.LastTXTriggerTick = MRF24J40IF_GetSysMilliseconds(); // record time (used to check for locked-up radio or PLL loss)

        }

        if (RadioStatus.TransmitCallback != NULL)
        {
        	RadioStatus.TransmitCallback();
        }
    }

    MRF24J40_InterruptEnable();
}

// inits Tx structure for simple point-to-point connection between a single pair of devices who both use the same address
// after calling this, you can send packets by just filling out:
// txPayload[] with payload and
// Tx.payloadLength,
// then calling RadioTXPacket()

void RadioInitP2P(void) {
    Tx.frameControl.Field.frameType = FRAME_TYPE_DATA;
    Tx.frameControl.Field.securityEnabled = 0x00;
    Tx.frameControl.Field.framePending = 0x00;
    Tx.frameControl.Field.ackRequest = 0x00;
    Tx.frameControl.Field.panIDcomp = 0x01;
    Tx.frameControl.Field.dstAddrMode = SHORT_ADDR_FIELD;
    Tx.frameControl.Field.frameVersion = 0;
    Tx.frameControl.Field.srcAddrMode = NO_ADDR_FIELD;
    Tx.dstPANID = RadioStatus.MyPANID;
    Tx.dstAddr = MY_SHORT_ADDRESS;
    //Tx.srcAddrMode = SHORT_ADDR_FIELD;
}


void MRF24J40_InstallCallback(uint8_t callbackType, void (*func)(void))
{
	if (RECEIVE_CALLBACK == callbackType)
	{
		RadioStatus.ReceiveCallback = func;
	}
	else if (TRANSMIT_CALLBACK == callbackType)
	{
		RadioStatus.TransmitCallback = func;
	}
}

void RadioInitBeaconCoord(void)
{
    lowWrite(RXMCR, PANCOORD);
    lowWrite(TXMCR, SLOTTED);


}

void ZigBeeDisable(void)
{

    MRF24J40_Disable();

}
