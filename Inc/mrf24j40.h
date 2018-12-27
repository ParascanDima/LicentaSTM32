/*
 * mrf24j40.h
 *
 *  Created on: 27 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef MRF24J40_H_
#define MRF24J40_H_


/***************************Imports*************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "mrf24j40ma_pinout.h"

/***************************Public Macro Definitions********************************/

// radio config
#define MY_LONG_ADDRESS         (0x0123456789abcdefull)     // device MAC address (8 bytes, 64 bit)
#define SERVER_SHORT_ADDRESS    (0xaa55)
#define MY_PAN_ID               (0x0f00)                    // PAN identifier
#define MY_SHORT_ADDRESS        (0xaa56)

#define PACKET_BUFFERS (2)                              // radio RX packet buffers.  Must be a power of 2.
//#define TURBO_MODE                                    // propriatary MCHP modulation; up to 625 Kbps (less range tho)
//#define ENABLE_PA_LNA                                 // for range on MB board

// hw setup

#define ONE_BYTE      1
#define TWO_BYTES     2
#define FOUR_BYTES    4
#define EIGHT_BYTES   8


#define BIT_0          0
#define BIT_1          1
#define BIT_2          2
#define BIT_3          3
#define BIT_4          4
#define BIT_5          5
#define BIT_6          6
#define BIT_7          7


#if defined(ENABLE_PA_LNA)
//  MB (high power) board has SiGe PA2423L, gain is nominally +22.5 dBm with 45% power-added efficiency
//  For use in USA, set output power set to be -1.9dB with 0x18 (FCC limit is 100 mW)
//  For use in Europe (and to be safe, elsewhere) set at -14.9dB with 0x70 (EU limit is 10 mW)
    #define TX_POWER            (0x18)      // use 0x18 for USA, 0x70 for Europe (and elsewhere, to be safe); uses SiGe PA2423L power amp
    #define FULL_CHANNEL_MAP    0x03FFF800  // 0b0000 0011 1111 1111 1111 1000 0000 0000 = bits 11 to 25 (for higher power MB module)
#else
    #define TX_POWER            (0x00)      // power level to be 0dBms
    #define FULL_CHANNEL_MAP    0x07FFF800  // 0b0000 0111 1111 1111 1111 1000 0000 0000 = bits 11 to 26 (for MA module)
#endif

#define RX_BUFFER_SIZE          (RX_FIFO_MEM_SIZE)  // 144 bytes per MRF24J40 data sheet figure 2-6
#define TX_FIFO_SIZE            (TX_NORMAL_FIFO_MEM_SIZE)// size of TX FIFO buffer in radio hardware
#define TX_PAYLOAD_SIZE         (103)               // max app payload size, bytes
#define RX_PAYLOAD_SIZE         (TX_PAYLOAD_SIZE)

#define FRAME_LENGTH_BYTES                (ONE_BYTE)
#define FRAME_CONTROL_BYTES               (TWO_BYTES)
#define SEQUENCE_NUMBER_BYTES             (ONE_BYTE)
#define MAX_DST_PANID_BYTES               (TWO_BYTES)
#define MAX_DST_ADDR_BYTES                (EIGHT_BYTES)
#define MAX_SRC_PANID_BYTES               (TWO_BYTES)
#define MAX_SRC_ADDR_BYTES                (EIGHT_BYTES)
#define MAX_AUX_SECURITY_HEADER_BYTES     (EIGHT_BYTES + FOUR_BYTES + TWO_BYTES)


    // note these have the same values as Frame Types in Table 79 of 802.15.4-2006
#define FRAME_TYPE_BEACON               0x00
#define FRAME_TYPE_DATA                 0x01
#define FRAME_TYPE_ACK                  0x02
#define FRAME_TYPE_MAC_COMMAND          0x03

// source and destination addressing modes, IEEE 802.15.4-2006 Table 80
#define NO_ADDR_FIELD       (0) // 00 PAN identifier and address fields are not present.
//#define RESERVED_FIELD    (1)    01 Reserved.
#define SHORT_ADDR_FIELD    (2) // 10 Address field contains a 16-bit short address.
#define LONG_ADDR_FIELD     (3) // 11 Address field contains a 64-bit extended address.

#define TX_RESULT_BUSY      (0)
#define TX_RESULT_SUCCESS   (1)
#define TX_RESULT_FAILED    (TX_RESULT_SUCCESS+1)


#define NO_SECURITY_LEVEL   (0x00)
#define SECURITY_LEVEL_1    (0x01)
#define SECURITY_LEVEL_2    (0x02)
#define SECURITY_LEVEL_3    (0x03)
#define SECURITY_LEVEL_4    (0x04)
#define SECURITY_LEVEL_5    (0x05)
#define SECURITY_LEVEL_6    (0x06)
#define SECURITY_LEVEL_7    (0x07)


#define KEY_ID_MODE_IMPLICIT  (0x00)
#define KEY_ID_MODE_1BYTE     (0x01)
#define KEY_ID_MODE_4BYTE     (0x02)
#define KEY_ID_MODE_8BYTE     (0x03)

#define FCS_OCTETS            (0x02)

#define START_UP              (0x01)   // Considering the start up as first reset


// converts x to a uint8_t* for bytewise access a.k.a. x[foo]
#define BYTEPTR(x)              ((uint8_t*)&(x))

#define ZIGBEE_UNINITIALIZED (ZigBeeStateType)0
#define ZIGBEE_INITIALIZED   (ZigBeeStateType)1
/***************************Public Type Definitions********************************/

typedef union                   // interrupt mask for radio
{
    uint8_t Val;
    struct
    {
        uint8_t TXIFG       :1; // transmission finished interrupt (TX no longer busy)
        uint8_t             :2;
        uint8_t RXIFG       :1; // received a packet interrupt
        uint8_t SECIFG      :1; // received a secured packet interrupt
        uint8_t             :4;
    } bits;
} MRF24J40_IFREG;

typedef struct                                  // radio state
{

    uint16_t            RXSecurityEnabled;                  // number of packets RX's with security bit set (had to discard)
    uint16_t            RadioExtraDiscard;                  // number of times we attempted to discard a packet that wasn't there (error)
    uint32_t            LastTXTriggerTick;                  // tick at which we triggered the last TX packet to go out
    uint16_t            MyShortAddress;                     // short (2 byte) address
    uint16_t            ServerShortAddress;
    uint16_t            MyPANID;                            // PANID (2 bytes)

    uint8_t             TX_BUSY         :1;                 // transmitter is busy.  Set when TX triggered, reset by TX ISR.
    uint8_t             TX_PENDING_ACK  :1;                 // we are currently waiting for an ack (don't know yet if we'll get one)
    uint8_t             TX_FAIL         :1;                 // last packet sent failed
    uint8_t             TX_RETRIES      :2;                 // number of tx retries of last sent packet
    uint8_t             TX_CCAFAIL      :1;                 // tells if last tx failed due to channel too busy
    uint8_t             SLEEPING        :1;                 // tells if radio is asleep now

    uint32_t            ResetCount;                         // count of times hardware has been reset
    uint64_t            MyLongAddress;                      // long (8 byte, MAC) address

    uint8_t volatile    RXPacketCount;                      // number of buffers waiting to be read (modified by ISR)
    uint8_t             IEEESeqNum;                         // tx packet sequence number (initial value not important)
    uint8_t             Channel;                            // current radio channel
} MRF24J40_STATUS;

typedef uint8_t ZigBeeStateType;

typedef union {
    uint16_t    value;
    struct {
        unsigned    frameType       :3;     // per Table 79
        unsigned    securityEnabled :1;     // per Figure 42
        unsigned    framePending    :1;     // per Figure 42
        unsigned    ackRequest      :1;     // per Figure 42
        unsigned    panIDcomp       :1;     // per Figure 42
        unsigned    /*reserved*/    :3;     // RESERVED bits in 802.15.4
        unsigned    dstAddrMode     :2;     // per Table 80
        unsigned    frameVersion    :2;     // per Figure 42
        unsigned    srcAddrMode     :2;     // per Table 80
    }Field;
}FrameCtrl;

typedef union{
    uint8_t value;
    struct{
        unsigned       securityLevel    :3;
        unsigned       keyIdMode        :2;
        unsigned       /*reserved*/     :3;
    }Field;
}SecurityCtrl;    // per Figure 63

typedef struct{
    uint64_t keySource;
    uint8_t keyIndex;
}KeyIdType;

typedef struct{

    //1 octet
    SecurityCtrl securityControl;

    //4 octets
    uint32_t frameCounter;

    //9 octets maximum
    KeyIdType keyID;

}AuxSecurityType;    // per Figure 62

typedef struct
{
    // note that the 1st 4 bytes of this structure are identical to the 1st 4 bytes of the RX FIFO contents

    FrameCtrl   frameControl;
    uint8_t     frameNumber;            // packet sequence number
    uint8_t     frameLength;            // bytes (m+n, per 802.15.4)  Does not count itself, 2 bytes of FCS, 1 of LQI, or 1 of RSSI.
    uint8_t     headerLength;

    uint8_t     payloadLength;          // length of payload field
    uint8_t *   payload;                // points at payload start
    uint16_t    fcs;
    uint8_t     lqi;                    // LQI value for the received packet
    uint8_t     rssi;                   // RSSI value for the received packet

    AuxSecurityType auxSecurityHeader;

    // from here down is NOT (necessarily) identical to FIFO contents

    uint16_t    dstPANID;
    uint16_t    srcPANID;
    uint64_t    dstAddr;                // only 1st 2 bytes used if short addr
    uint64_t    srcAddr;                // only 1st 2 bytes used if short addr
} PACKET;

/***************************Public Data Definitions********************************/

extern MRF24J40_STATUS volatile RadioStatus;                        // radio state
extern PACKET Tx;                                                   // description of packet to be transmitted
extern PACKET Rx;                                                   // description of received packet (after parsing)


/***************************Public Function Definitions****************************/

uint8_t     RadioInit(void);
void        RadioSetAddress(uint16_t shortAddress, uint64_t longAddress, uint16_t panID);
uint8_t     RadioSetChannel(uint8_t channel);
void        RadioSetSleep(uint8_t powerState);
uint8_t     RadioEnergyDetect(void);
void        RadioTXRaw(void);
void        RadioTXPacket(void);
uint8_t     RadioRXPacket(void);
uint8_t     RadioTXResult(void);
uint8_t     RadioWaitTXResult(void);
void        RadioDiscardPacket(void);
void        ZigBeeDisable(void);
void        RadioInitP2P(void);
void        MRF24J40_ToSend(uint8_t* dataToSend, uint8_t length);
void        MRF24J40_EventHandler(void);
ZigBeeStateType MRF24J40_GetState(void);

#endif /* MRF24J40_H_ */
