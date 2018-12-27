/*
 * mrf24j40_memmap.h
 *
 *  Created on: 24 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef MRF24J40_MEMMAP_H_
#define MRF24J40_MEMMAP_H_


/***************************Imports*************************************************/

#include <stdint.h>
#include <stdbool.h>

/***************************Public Macro Definitions********************************/

#define MRF24J40_MEM_SECTIONS             (uint8_t)(9)


#define LOW_CONTROL_REGISTERS_START_ADDR  (uint8_t)(0x00)
#define LOW_CONTROL_REGISTERS_MEM_SIZE    (uint8_t)(0x40)
#define LOW_CONTROL_REGISTERS_END_ADDR    (uint8_t)(LOW_CONTROL_REGISTERS_START_ADDR+LOW_CONTROL_REGISTERS_MEM_SIZE-(uint8_t)1)


#define TX_NORMAL_FIFO_START_ADDR         (uint16_t)(0x000)
#define TX_NORMAL_FIFO_MEM_SIZE           (uint8_t) (0x80)
#define TX_NORMAL_FIFO_END_ADDR           (uint16_t)(TX_NORMAL_FIFO_START_ADDR+TX_NORMAL_FIFO_MEM_SIZE-(uint8_t)1)


#define TX_BEACON_FIFO_START_ADDR         (uint16_t)(0x080)
#define TX_BEACON_FIFO_MEM_SIZE           (uint8_t)(0x80)
#define TX_BEACON_FIFO_END_ADDR           (uint16_t)(TX_BEACON_FIFO_START_ADDR+TX_BEACON_FIFO_MEM_SIZE-(uint8_t)1)


#define TX_GTS1_FIFO_START_ADDR           (uint16_t)(0x100)
#define TX_GTS1_FIFO_MEM_SIZE             (uint16_t)(0x80)
#define TX_GTS1_FIFO_END_ADDR             (uint16_t)(TX_GTS1_FIFO_START_ADDR+TX_GTS1_FIFO_MEM_SIZE-(uint8_t)1)


#define TX_GTS2_FIFO_START_ADDR           (uint16_t)(0x180)
#define TX_GTS2_FIFO_MEM_SIZE             (uint8_t)(0x80)
#define TX_GTS2_FIFO_END_ADDR             (uint16_t)(TX_GTS2_FIFO_START_ADDR+TX_GTS2_FIFO_MEM_SIZE-(uint8_t)1)


#define HIGH_CONTROL_REGISTERS_START_ADDR (uint16_t)(0x200)
#define HIGH_CONTROL_REGISTERS_MEM_SIZE   (uint8_t)(0x80)
#define HIGH_CONTROL_REGISTERS_END_ADDR   (uint16_t)(HIGH_CONTROL_REGISTERS_START_ADDR+HIGH_CONTROL_REGISTERS_MEM_SIZE-(uint8_t)1)


#define SECURITY_KEY_FIFO_START_ADDR      (uint16_t)(0x280)
#define SECURITY_KEY_FIFO_MEM_SIZE        (uint8_t)(0x40)
#define SECURITY_KEY_FIFO_END_ADDR        (uint16_t)(SECURITY_KEY_FIFO_START_ADDR+SECURITY_KEY_FIFO_MEM_SIZE-(uint8_t)1)


#define RESERVED_START_ADDR               (uint16_t)(0x2C0)
#define RESERVED_MEM_SIZE                 (uint8_t)(0x40)
#define RESERVED_END_ADDR                 (uint16_t)(RESERVED_START_ADDR+RESERVED_MEM_SIZE-(uint8_t)1)


#define RX_FIFO_START_ADDR                (uint16_t)(0x300)
#define RX_FIFO_MEM_SIZE                  (uint8_t)(0x90)
#define RX_FIFO_END_ADDR                  (uint16_t)(RX_FIFO_START_ADDR+RX_FIFO_MEM_SIZE-(uint8_t)1)



#define LOW_CONTROL_REGISTERS_SECTION     (uint8_t)(0x00)
#define TX_NORMAL_FIFO_SECTION            (uint8_t)(0x01)
#define TX_BEACON_FIFO_SECTION            (uint8_t)(0x02)
#define TX_GTS1_FIFO_SECTION              (uint8_t)(0x03)
#define TX_GTS2_FIFO_SECTION              (uint8_t)(0x04)
#define HIGH_CONTROL_REGISTERS_SECTION    (uint8_t)(0x05)
#define SECURITY_KEY_FIFO_SECTION         (uint8_t)(0x06)
#define RESERVED_SECTION                  (uint8_t)(0x07)
#define RX_FIFO_SECTION                   (uint8_t)(0x08)




// MRF24J40 hardware register definitions


//---------------------------------------Long address registers
#define RFCON0             (uint16_t)(0x200)
#define RFCON1             (uint16_t)(0x201)
#define RFCON2             (uint16_t)(0x202)
#define RFCON3             (uint16_t)(0x203)
//#define RESERVED         (uint16_t)     (0x204)
#define RFCON5             (uint16_t)(0x205)
#define RFCON6             (uint16_t)(0x206)
#define RFCON7             (uint16_t)(0x207)
#define RFCON8             (uint16_t)(0x208)
#define SLPCAL0            (uint16_t)(0x209)
#define SLPCAL1            (uint16_t)(0x20a)
#define SLPCAL2            (uint16_t)(0x20b)
//#define RESERVED         (uint16_t)     (0x20c)
//#define RESERVED         (uint16_t)     (0x20d)
//#define RESERVED         (uint16_t)     (0x20e)
#define RFSTATE            (uint16_t)(0x20f)
#define RSSI               (uint16_t)(0x210)
#define SLPCON0            (uint16_t)(0x211)
//#define RESERVED         (uint16_t)     (0x212)
//#define RESERVED         (uint16_t)     (0x213)
//#define RESERVED         (uint16_t)     (0x214)
//#define RESERVED         (uint16_t)     (0x215)
//#define RESERVED         (uint16_t)     (0x216)
//#define RESERVED         (uint16_t)     (0x217)
//#define RESERVED         (uint16_t)     (0x218)
//#define RESERVED         (uint16_t)     (0x219)
//#define RESERVED         (uint16_t)     (0x21a)
//#define RESERVED         (uint16_t)     (0x21b)
//#define RESERVED         (uint16_t)     (0x21c)
//#define RESERVED         (uint16_t)     (0x21d)
//#define RESERVED         (uint16_t)     (0x21e)
//#define RESERVED         (uint16_t)     (0x21f)
#define SLPCON1            (uint16_t)(0x220)
//#define RESERVED         (uint16_t)     (0x221)
#define WAKETIMEL          (uint16_t)(0x222)
#define WAKETIMEH          (uint16_t)(0x223)
#define REMCNTL            (uint16_t)(0x224)
#define REMCNTH            (uint16_t)(0x225)
#define MAINCNT0           (uint16_t)(0x226)
#define MAINCNT1           (uint16_t)(0x227)
#define MAINCNT2           (uint16_t)(0x228)
#define MAINCNT3           (uint16_t)(0x229)
//#define RESERVED         (uint16_t)     (0x22a)
//#define RESERVED         (uint16_t)     (0x22b)
//#define RESERVED         (uint16_t)     (0x22c)
//#define RESERVED         (uint16_t)     (0x22d)
//#define RESERVED         (uint16_t)     (0x22e)
#define TESTMODE           (uint16_t)(0x22f)
#define ASSOEADR0          (uint16_t)(0x230)
#define ASSOEADR1          (uint16_t)(0x231)
#define ASSOEADR2          (uint16_t)(0x232)
#define ASSOEADR3          (uint16_t)(0x233)
#define ASSOEADR4          (uint16_t)(0x234)
#define ASSOEADR5          (uint16_t)(0x235)
#define ASSOEADR6          (uint16_t)(0x236)
#define ASSOEADR7          (uint16_t)(0x237)
#define ASSOSADR0          (uint16_t)(0x238)
#define ASSOSADR1          (uint16_t)(0x239)
//#define RESERVED         (uint16_t)     (0x23a)
//#define RESERVED         (uint16_t)     (0x23b)
//#define unimplemented    (uint16_t)     (0x23c)
//#define unimplemented    (uint16_t)     (0x23d)
//#define unimplemented    (uint16_t)     (0x23e)
//#define unimplemented    (uint16_t)     (0x23f)
#define UPNONCE0           (uint16_t)(0x240)
#define UPNONCE1           (uint16_t)(0x241)
#define UPNONCE2           (uint16_t)(0x242)
#define UPNONCE3           (uint16_t)(0x243)
#define UPNONCE4           (uint16_t)(0x244)
#define UPNONCE5           (uint16_t)(0x245)
#define UPNONCE6           (uint16_t)(0x246)
#define UPNONCE7           (uint16_t)(0x247)
#define UPNONCE8           (uint16_t)(0x248)
#define UPNONCE9           (uint16_t)(0x249)
#define UPNONCE10          (uint16_t)(0x24a)
#define UPNONCE11          (uint16_t)(0x24b)
#define UPNONCE12          (uint16_t)(0x24c)




//------------------------------Short address registers
#define RXMCR              (uint8_t)(0x00)
#define PANIDL             (uint8_t)(0x01)
#define PANIDH             (uint8_t)(0x02)
#define SADRL              (uint8_t)(0x03)
#define SADRH              (uint8_t)(0x04)
#define EADR0              (uint8_t)(0x05)
#define EADR1              (uint8_t)(0x06)
#define EADR2              (uint8_t)(0x07)
#define EADR3              (uint8_t)(0x08)
#define EADR4              (uint8_t)(0x09)
#define EADR5              (uint8_t)(0x0A)
#define EADR6              (uint8_t)(0x0B)
#define EADR7              (uint8_t)(0x0C)
#define RXFLUSH            (uint8_t)(0x0D)
//#define RESERVED         (uint8_t)  (0x0E)
//#define RESERVED         (uint8_t)  (0x0F)
#define ORDER              (uint8_t)(0x10)
#define TXMCR              (uint8_t)(0x11)
#define ACKTMOUT           (uint8_t)(0x12)
#define ESLOTG1            (uint8_t)(0x13)
#define SYMTICKL           (uint8_t)(0x14)
#define SYMTICKH           (uint8_t)(0x15)
#define PACON0             (uint8_t)(0x16)
#define PACON1             (uint8_t)(0x17)
#define PACON2             (uint8_t)(0x18)
//#define RESERVED         (uint8_t)    (0x19)
#define TXBCON0            (uint8_t)(0x1A)
#define TXNCON             (uint8_t)(0x1B)
#define TXG1CON            (uint8_t)(0x1C)
#define TXG2CON            (uint8_t)(0x1D)
#define ESLOTG23           (uint8_t)(0x1E)
#define ESLOTG45           (uint8_t)(0x1F)
#define ESLOTG67           (uint8_t)(0x20)
#define TXPEND             (uint8_t)(0x21)
#define WAKECON            (uint8_t)(0x22)
#define FRMOFFSET          (uint8_t)(0x23)
#define TXSTAT             (uint8_t)(0x24)
#define TXBCON1            (uint8_t)(0x25)
#define GATECLK            (uint8_t)(0x26)
#define TXTIME             (uint8_t)(0x27)
#define HSYMTMRL           (uint8_t)(0x28)
#define HSYMTMRH           (uint8_t)(0x29)
#define SOFTRST            (uint8_t)(0x2A)
//#define RESERVED         (uint8_t)    (0x2B)
#define SECCON0            (uint8_t)(0x2C)
#define SECCON1            (uint8_t)(0x2D)
#define TXSTBL             (uint8_t)(0x2E)
//#define RESERVED         (uint8_t)    (0x2F)
#define RXSR               (uint8_t)(0x30)
#define INTSTAT            (uint8_t)(0x31)
#define INTCON             (uint8_t)(0x32)
#define GPIO               (uint8_t)(0x33)
#define TRISGPIO           (uint8_t)(0x34)
#define SLPACK             (uint8_t)(0x35)
#define RFCTL              (uint8_t)(0x36)
#define SECCR2             (uint8_t)(0x37)
#define BBREG0             (uint8_t)(0x38)
#define BBREG1             (uint8_t)(0x39)
#define BBREG2             (uint8_t)(0x3A)
#define BBREG3             (uint8_t)(0x3B)
#define BBREG4             (uint8_t)(0x3C)
//#define RESERVED         (uint8_t)    (0x3D)
#define BBREG6             (uint8_t)(0x3E)
#define CCAEDTH            (uint8_t)(0x3F)




//-------------------------------------------Registers Bits:

//------Short address:

//                               RXMCR register:

//#define RESERVED           (0x80)
//#define RESERVED           (0x40)
#define NOACKRSP           (0x20)
//#define RESERVED           (0x10)
#define PANCOORD           (0x08)
#define COORD              (0x04)
#define ERRPKT             (0x02)
#define PROMI              (0x01)

//                                 PANIDL register:

#define PANIDL_7           (0x80)
#define PANIDL_6           (0x40)
#define PANIDL_5           (0x20)
#define PANIDL_4           (0x10)
#define PANIDL_3           (0x08)
#define PANIDL_2           (0x04)
#define PANIDL_1           (0x02)
#define PANIDL_0           (0x01)

//                                 PANIDH register:

#define PANIDH_7           (0x80)
#define PANIDH_6           (0x40)
#define PANIDH_5           (0x20)
#define PANIDH_4           (0x10)
#define PANIDH_3           (0x08)
#define PANIDH_2           (0x04)
#define PANIDH_1           (0x02)
#define PANIDH_0           (0x01)

//                                 SADRL register:

#define SADRL_7            (0x80)
#define SADRL_6            (0x40)
#define SADRL_5            (0x20)
#define SADRL_4            (0x10)
#define SADRL_3            (0x08)
#define SADRL_2            (0x04)
#define SADRL_1            (0x02)
#define SADRL_0            (0x01)

//                                 SADRH register:

#define SADRH_7            (0x80)
#define SADRH_6            (0x40)
#define SADRH_5            (0x20)
#define SADRH_4            (0x10)
#define SADRH_3            (0x08)
#define SADRH_2            (0x04)
#define SADRH_1            (0x02)
#define SADRH_0            (0x01)

//                                 EADR0 register:

#define EADR0_7            (0x80)
#define EADR0_6            (0x40)
#define EADR0_5            (0x20)
#define EADR0_4            (0x10)
#define EADR0_3            (0x08)
#define EADR0_2            (0x04)
#define EADR0_1            (0x02)
#define EADR0_0            (0x01)

//                                 EADR1 register:

#define EADR1_7            (0x80)
#define EADR1_6            (0x40)
#define EADR1_5            (0x20)
#define EADR1_4            (0x10)
#define EADR1_3            (0x08)
#define EADR1_2            (0x04)
#define EADR1_1            (0x02)
#define EADR1_0            (0x01)

//                                 EADR2 register:

#define EADR2_7            (0x80)
#define EADR2_6            (0x40)
#define EADR2_5            (0x20)
#define EADR2_4            (0x10)
#define EADR2_3            (0x08)
#define EADR2_2            (0x04)
#define EADR2_1            (0x02)
#define EADR2_0            (0x01)

//                                 EADR3 register:

#define EADR3_7            (0x80)
#define EADR3_6            (0x40)
#define EADR3_5            (0x20)
#define EADR3_4            (0x10)
#define EADR3_3            (0x08)
#define EADR3_2            (0x04)
#define EADR3_1            (0x02)
#define EADR3_0            (0x01)

//                                 EADR4 register:

#define EADR4_7            (0x80)
#define EADR4_6            (0x40)
#define EADR4_5            (0x20)
#define EADR4_4            (0x10)
#define EADR4_3            (0x08)
#define EADR4_2            (0x04)
#define EADR4_1            (0x02)
#define EADR4_0            (0x01)

//                                 EADR5 register:

#define EADR5_7            (0x80)
#define EADR5_6            (0x40)
#define EADR5_5            (0x20)
#define EADR5_4            (0x10)
#define EADR5_3            (0x08)
#define EADR5_2            (0x04)
#define EADR5_1            (0x02)
#define EADR5_0            (0x01)

//                                 EADR6 register:

#define EADR6_7            (0x80)
#define EADR6_6            (0x40)
#define EADR6_5            (0x20)
#define EADR6_4            (0x10)
#define EADR6_3            (0x08)
#define EADR6_2            (0x04)
#define EADR6_1            (0x02)
#define EADR6_0            (0x01)

//                                 EADR7 register:

#define EADR7_7            (0x80)
#define EADR7_6            (0x40)
#define EADR7_5            (0x20)
#define EADR7_4            (0x10)
#define EADR7_3            (0x08)
#define EADR7_2            (0x04)
#define EADR7_1            (0x02)
#define EADR7_0            (0x01)

//                                 RXFLUSH register:

//#define RESERVED            (0x80)
#define WAKEPOL            (0x40)
#define WAKEPAD            (0x20)
//#define RESERVED            (0x10)
#define CMDONLY            (0x08)
#define DATAONLY           (0x04)
#define BCNONLY            (0x02)
#define RXFLUSH_BIT        (0x01)

//                                 ORDER register:

#define BO3                (0x80)
#define BO2                (0x40)
#define BO1                (0x20)
#define BO0                (0x10)
#define SO3                (0x08)
#define SO2                (0x04)
#define SO1                (0x02)
#define SO0                (0x01)

//                                 TXMCR register:

#define NOCSMA             (0x80)
#define BATLIFEXT          (0x40)
#define SLOTTED            (0x20)
#define MACMINBE1          (0x10)
#define MACMINBE0          (0x08)
#define CSMABF2            (0x04)
#define CSMABF1            (0x02)
#define CSMABF0            (0x01)

//                                 ACKTMOUT register:

#define DRPACK             (0x80)
#define MAWD6              (0x40)
#define MAWD5              (0x20)
#define MAWD4              (0x10)
#define MAWD3              (0x08)
#define MAWD2              (0x04)
#define MAWD1              (0x02)
#define MAWD0              (0x01)

//                                 ESLOTG1 register:

#define GTS1_3             (0x80)
#define GTS1_2             (0x40)
#define GTS1_1             (0x20)
#define GTS1_0             (0x10)
#define CAP3               (0x08)
#define CAP2               (0x04)
#define CAP1               (0x02)
#define CAP0               (0x01)

//                                 SYMTICKL register:

#define TICKP7             (0x80)
#define TICKP6             (0x40)
#define TICKP5             (0x20)
#define TICKP4             (0x10)
#define TICKP3             (0x08)
#define TICKP2             (0x04)
#define TICKP1             (0x02)
#define TICKP0             (0x01)

//                                 SYMTICKH register:

#define TXONT6             (0x80)
#define TXONT5             (0x40)
#define TXONT4             (0x20)
#define TXONT3             (0x10)
#define TXONT2             (0x08)
#define TXONT1             (0x04)
#define TXONT0             (0x02)
#define TICKP8             (0x01)

//                                 PACON0 register:

#define PAONT7             (0x80)
#define PAONT6             (0x40)
#define PAONT5             (0x20)
#define PAONT4             (0x10)
#define PAONT3             (0x08)
#define PAONT2             (0x04)
#define PAONT1             (0x02)
#define PAONT0             (0x01)

//                                 PACON1 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define PAONTS3            (0x10)
#define PAONTS2            (0x08)
#define PAONTS1            (0x04)
#define PAONTS0            (0x02)
#define PAONT8             (0x01)

//                                 PACON2 register:

#define FIFOEN             (0x80)
//#define RESERVED             (0x40)
#define TXONTS3            (0x20)
#define TXONTS2            (0x10)
#define TXONTS1            (0x08)
#define TXONTS0            (0x04)
#define TXONT8             (0x02)
#define TXONT7             (0x01)

//                                 TXBCON0 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
#define TXBSECEN           (0x02)
#define TXBTRIG            (0x01)

//                                 TXNCON register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define FPSTAT             (0x10)
#define INDIRECT           (0x08)
#define TXNACKREQ          (0x04)
#define TXNSECEN           (0x02)
#define TXNTRIG            (0x01)

//                                 TXG1CON register:

#define TXG1RETRY1         (0x80)
#define TXG1RETRY0         (0x40)
#define TXG1SLOT2          (0x20)
#define TXG1SLOT1          (0x10)
#define TXG1SLOT0          (0x08)
#define TXG1ACKREQ         (0x04)
#define TXG1SECEN          (0x02)
#define TXG1TRIG           (0x01)

//                                 TXG2CON register:

#define TXG2RETRY1         (0x80)
#define TXG2RETRY0         (0x40)
#define TXG2SLOT2          (0x20)
#define TXG2SLOT1          (0x10)
#define TXG2SLOT0          (0x08)
#define TXG2ACKREQ         (0x04)
#define TXG2SECEN          (0x02)
#define TXG2TRIG           (0x01)

//                                 ESLOTG23 register:

#define GTS3_3             (0x80)
#define GTS3_2             (0x40)
#define GTS3_1             (0x20)
#define GTS3_0             (0x10)
#define GTS2_3             (0x08)
#define GTS2_2             (0x04)
#define GTS2_1             (0x02)
#define GTS2_0             (0x01)

//                                 ESLOTG45 register:

#define GTS5_3             (0x80)
#define GTS5_2             (0x40)
#define GTS5_1             (0x20)
#define GTS5_0             (0x10)
#define GTS4_3             (0x08)
#define GTS4_2             (0x04)
#define GTS4_1             (0x02)
#define GTS4_0             (0x01)

//                                 ESLOTG67 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
#define GTS6_3             (0x08)
#define GTS6_2             (0x04)
#define GTS6_1             (0x02)
#define GTS6_0             (0x01)

//                                 TXPEND register:

#define MLIFS_5            (0x80)
#define MLIFS_4            (0x40)
#define MLIFS_3            (0x20)
#define MLIFS_2            (0x10)
#define MLIFS_1            (0x08)
#define MLIFS_0            (0x04)
#define GTSSWITCH          (0x02)
#define FPACK              (0x01)

//                                 WAKECON register:

#define IMMWAKE            (0x80)
#define REGWAKE            (0x40)
#define INTL_5             (0x20)
#define INTL_4             (0x10)
#define INTL_3             (0x08)
#define INTL_2             (0x04)
#define INTL_1             (0x02)
#define INTL_0             (0x01)

//                                 FRMOFFSET register:

#define OFFSET_7           (0x80)
#define OFFSET_6           (0x40)
#define OFFSET_5           (0x20)
#define OFFSET_4           (0x10)
#define OFFSET_3           (0x08)
#define OFFSET_2           (0x04)
#define OFFSET_1           (0x02)
#define OFFSET_0           (0x01)

//                                 TXSTAT register:

#define TXNRETRY_1         (0x80)
#define TXNRETRY_0         (0x40)
#define CCAFAIL            (0x20)
#define TXG2FNT            (0x10)
#define TXG1FNT            (0x08)
#define TXG2STAT           (0x04)
#define TXG1STAT           (0x02)
#define TXNSTAT            (0x01)

//                                 TXBCON1 register:

#define TXBMSK             (0x80)
#define WU_BCN             (0x40)
#define RSSINUM_1          (0x20)
#define RSSINUM_0          (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 GATECLK register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
#define TXG1FNT            (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 TXTIME register:

#define TURNTIME_3         (0x80)
#define TURNTIME_2         (0x40)
#define TURNTIME_1         (0x20)
#define TURNTIME_0         (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 HSYMTMRL register:

#define HSYMTMR_7          (0x80)
#define HSYMTMR_6          (0x40)
#define HSYMTMR_5          (0x20)
#define HSYMTMR_4          (0x10)
#define HSYMTMR_3          (0x08)
#define HSYMTMR_2          (0x04)
#define HSYMTMR_1          (0x02)
#define HSYMTMR_0          (0x01)

//                                 HSYMTMRH register:

#define HSYMTMR_15         (0x80)
#define HSYMTMR_14         (0x40)
#define HSYMTMR_13         (0x20)
#define HSYMTMR_12         (0x10)
#define HSYMTMR_11         (0x08)
#define HSYMTMR_10         (0x04)
#define HSYMTMR_9          (0x02)
#define HSYMTMR_8          (0x01)

//                                 SOFTRST register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
#define RSTPWR             (0x04)
#define RSTBB              (0x02)
#define RSTMAC             (0x01)

//                                 SECCON0 register:

#define SECIGNORE          (0x80)
#define SECSTART           (0x40)
#define RXCIPHER_2         (0x20)
#define RXCIPHER_1         (0x10)
#define RXCIPHER_0         (0x08)
#define TXNCIPHER_2        (0x04)
#define TXNCIPHER_1        (0x02)
#define TXNCIPHER_0        (0x01)

//                                 SECCON1 register:

//#define RESERVED             (0x80)
#define TXBCIPHER_2        (0x40)
#define TXBCIPHER_1        (0x20)
#define TXBCIPHER_0        (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
#define DISDEC             (0x02)
#define DISENC             (0x01)

//                                 TXSTBL register:

#define RFSTBL_3           (0x80)
#define RFSTBL_2           (0x40)
#define RFSTBL_1           (0x20)
#define RFSTBL_0           (0x10)
#define MSIFS_3            (0x08)
#define MSIFS_2            (0x04)
#define MSIFS_1            (0x02)
#define MSIFS_0            (0x01)

//                                 RXSR register:

//#define RESERVED             (0x80)
#define UPSECER            (0x40)
#define BATIND             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
#define SECDECERR          (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 INTSTAT register:

#define SLPIF              (0x80)
#define WAKEIF             (0x40)
#define HSYMTMRIF          (0x20)
#define SECIF              (0x10)
#define RXIF               (0x08)
#define TXG2IF             (0x04)
#define TXG1IF             (0x02)
#define TXNIF              (0x01)

//                                 INTCON register:

#define SLPIE              (0x80)
#define WAKEIE             (0x40)
#define HSYMTMRIE          (0x20)
#define SECIE              (0x10)
#define RXIE               (0x08)
#define TXG2IE             (0x04)
#define TXG1IE             (0x02)
#define TXNIE              (0x01)

//                                 GPIO register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
#define GPIO_5             (0x20)
#define GPIO_4             (0x10)
#define GPIO_3             (0x08)
#define GPIO_2             (0x04)
#define GPIO_1             (0x02)
#define GPIO_0             (0x01)

//                                 TRISGPIO register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
#define TRISGP_5           (0x20)
#define TRISGP_4           (0x10)
#define TRISGP_3           (0x08)
#define TRISGP_2           (0x04)
#define TRISGP_1           (0x02)
#define TRISGP_0           (0x01)

//                                 SLPACK register:

#define SLPACK_BIT         (0x80)
#define WAKECNT_6          (0x40)
#define WAKECNT_5          (0x20)
#define WAKECNT_4          (0x10)
#define WAKECNT_3          (0x08)
#define WAKECNT_2          (0x04)
#define WAKECNT_1          (0x02)
#define WAKECNT_0          (0x01)

//                                 RFCTL register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define WAKECNT_8          (0x10)
#define WAKECNT_7          (0x08)
#define RFRST              (0x04)
#define RFTXMODE           (0x02)
#define RFRXMODE           (0x01)

//                                 SECCR2 register:

#define UPDEC              (0x80)
#define UPENC              (0x40)
#define TXG2CIPHER_2       (0x20)
#define TXG2CIPHER_1       (0x10)
#define TXG2CIPHER_0       (0x08)
#define TXG1CIPHER_2       (0x04)
#define TXG1CIPHER_1       (0x02)
#define TXG1CIPHER_0       (0x01)

//                                 BBREG0 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
#define TURBO              (0x01)

//                                 BBREG1 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
#define RXDECINV           (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 BBREG2 register:

#define CCAMO              (0x80)
#define CCAMODE_0          (0x40)
#define CCACSTH_3          (0x20)
#define CCACSTH_2          (0x10)
#define CCACSTH_1          (0x08)
#define CCACSTH_0          (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 BBREG3 register:

#define PREVALIDTH_3       (0x80)
#define PREVALIDTH_2       (0x40)
#define PREVALIDTH_1       (0x20)
#define PREVALIDTH_0       (0x10)
#define PREDETTH_2         (0x08)
#define PREDETTH_1         (0x04)
#define PREDETTH_0         (0x02)
//#define RESERVED             (0x01)

//                                 BBREG4 register:

#define CSTH_2             (0x80)
#define CSTH_1             (0x40)
#define CSTH_0             (0x20)
#define PRECNT_2           (0x10)
#define PRECNT_1           (0x08)
#define PRECNT_0           (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 BBREG6 register:

#define RSSIMODE_1         (0x80)
#define RSSIMODE_2         (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
#define RSSIRDY            (0x01)

//                                 CCAEDTH register:

#define CCAEDTH_7          (0x80)
#define CCAEDTH_6          (0x40)
#define CCAEDTH_5          (0x20)
#define CCAEDTH_4          (0x10)
#define CCAEDTH_3          (0x08)
#define CCAEDTH_2          (0x04)
#define CCAEDTH_1          (0x02)
#define CCAEDTH_0          (0x01)



//------Long address:

//                                 RFCON0 register:

#define CHANNEL_3          (0x80)
#define CHANNEL_2          (0x40)
#define CHANNEL_1          (0x20)
#define CHANNEL_0          (0x10)
#define RFOPT_3            (0x08)
#define RFOPT_2            (0x04)
#define RFOPT_1            (0x02)
#define RFOPT_0            (0x01)

//                                 RFCON1 register:

#define VCOOPT_7           (0x80)
#define VCOOPT_6           (0x40)
#define VCOOPT_5           (0x20)
#define VCOOPT_4           (0x10)
#define VCOOPT_3           (0x08)
#define VCOOPT_2           (0x04)
#define VCOOPT_1           (0x02)
#define VCOOPT_0           (0x01)

//                                 RFCON2 register:

#define PLLEN              (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 RFCON3 register:

#define TXPWRL_1           (0x80)
#define TXPWRL_0           (0x40)
#define TXPWRS_2           (0x20)
#define TXPWRS_1           (0x10)
#define TXPWRS_0           (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 RFCON5 register:

#define BATTH_3            (0x80)
#define BATTH_2            (0x40)
#define BATTH_1            (0x20)
#define BATTH_0            (0x10)
//#define RESERVED            (0x08)
//#define RESERVED            (0x04)
//#define RESERVED            (0x02)
//#define RESERVED            (0x01)

//                                 RFCON6 register:

#define TXFIL              (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define _20MRECVR          (0x10)
#define BATEN              (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 RFCON7 register:

#define SLPCLKSEL_1        (0x80)
#define SLPCLKSEL_0        (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
#define CLKOUTMODE_1       (0x02)
#define CLKOUTMODE_0       (0x01)

//                                 RFCON8 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define RFVCO              (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 SLPCAL0 register:

#define SLPCAL_7           (0x80)
#define SLPCAL_6           (0x40)
#define SLPCAL_5           (0x20)
#define SLPCAL_4           (0x10)
#define SLPCAL_3           (0x08)
#define SLPCAL_2           (0x04)
#define SLPCAL_1           (0x02)
#define SLPCAL_0           (0x01)

//                                 SLPCAL1 register:

#define SLPCAL_15          (0x80)
#define SLPCAL_14          (0x40)
#define SLPCAL_13          (0x20)
#define SLPCAL_12          (0x10)
#define SLPCAL_11          (0x08)
#define SLPCAL_10          (0x04)
#define SLPCAL_9           (0x02)
#define SLPCAL_8           (0x01)

//                                 SLPCAL2 register:

#define SLPCALRDY          (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define SLPCALEN           (0x10)
#define SLPCAL_19          (0x08)
#define SLPCAL_18          (0x04)
#define SLPCAL_17          (0x02)
#define SLPCAL_16          (0x01)

//                                 RFSTATE register:

#define RFSTATE_2          (0x80)
#define RFSTATE_1          (0x40)
#define RFSTATE_0          (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
//#define RESERVED             (0x02)
//#define RESERVED             (0x01)

//                                 RSSI register:

#define RSSI_7             (0x80)
#define RSSI_6             (0x40)
#define RSSI_5             (0x20)
#define RSSI_4             (0x10)
#define RSSI_3             (0x08)
#define RSSI_2             (0x04)
#define RSSI_1             (0x02)
#define RSSI_0             (0x01)

//                                 SLPCON0 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
#define INTEDGE            (0x02)
#define SLPCLKEN           (0x01)

//                                 SLPCON1 register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
#define CLKOUTEN           (0x20)
#define SLPCLKDIV_4        (0x10)
#define SLPCLKDIV_3        (0x08)
#define SLPCLKDIV_2        (0x04)
#define SLPCLKDIV_1        (0x02)
#define SLPCLKDIV_0        (0x01)

//                                 WAKETIMEL register:

#define WAKETIME_7         (0x80)
#define WAKETIME_6         (0x40)
#define WAKETIME_5         (0x20)
#define WAKETIME_4         (0x10)
#define WAKETIME_3         (0x08)
#define WAKETIME_2         (0x04)
#define WAKETIME_1         (0x02)
#define WAKETIME_0         (0x01)

//                                 WAKETIMEH register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
#define WAKETIME_10        (0x04)
#define WAKETIME_9         (0x02)
#define WAKETIME_8         (0x01)

//                                 REMCNTL register:

#define REMCNT_7           (0x80)
#define REMCNT_6           (0x40)
#define REMCNT_5           (0x20)
#define REMCNT_4           (0x10)
#define REMCNT_3           (0x08)
#define REMCNT_2           (0x04)
#define REMCNT_1           (0x02)
#define REMCNT_0           (0x01)

//                                 REMCNTH register:

#define REMCNT_15          (0x80)
#define REMCNT_14          (0x40)
#define REMCNT_13          (0x20)
#define REMCNT_12          (0x10)
#define REMCNT_11          (0x08)
#define REMCNT_10          (0x04)
#define REMCNT_9           (0x02)
#define REMCNT_8           (0x01)

//                                 MAINCNT0 register:

#define MAINCNT_7          (0x80)
#define MAINCNT_6          (0x40)
#define MAINCNT_5          (0x20)
#define MAINCNT_4          (0x10)
#define MAINCNT_3          (0x08)
#define MAINCNT_2          (0x04)
#define MAINCNT_1          (0x02)
#define MAINCNT_0          (0x01)

//                                 MAINCNT1 register:

#define MAINCNT_15         (0x80)
#define MAINCNT_14         (0x40)
#define MAINCNT_13         (0x20)
#define MAINCNT_12         (0x10)
#define MAINCNT_11         (0x08)
#define MAINCNT_10         (0x04)
#define MAINCNT_9          (0x02)
#define MAINCNT_8          (0x01)

//                                 MAINCNT2 register:

#define MAINCNT_23         (0x80)
#define MAINCNT_22         (0x40)
#define MAINCNT_21         (0x20)
#define MAINCNT_20         (0x10)
#define MAINCNT_19         (0x08)
#define MAINCNT_18         (0x04)
#define MAINCNT_17         (0x02)
#define MAINCNT_16         (0x01)

//                                 MAINCNT3 register:

#define STARTCNT           (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
//#define RESERVED             (0x10)
//#define RESERVED             (0x08)
//#define RESERVED             (0x04)
#define MAINCNT_25         (0x02)
#define MAINCNT_24         (0x01)

//                                 TESTMODE register:

//#define RESERVED             (0x80)
//#define RESERVED             (0x40)
//#define RESERVED             (0x20)
#define TESTMODE_4         (0x10)
#define TESTMODE_3         (0x08)
#define TESTMODE_2         (0x04)
#define TESTMODE_1         (0x02)
#define TESTMODE_0         (0x01)

//                                 ASSOEADR0 register:

#define ASSOEADR_7         (0x80)
#define ASSOEADR_6         (0x40)
#define ASSOEADR_5         (0x20)
#define ASSOEADR_4         (0x10)
#define ASSOEADR_3         (0x08)
#define ASSOEADR_2         (0x04)
#define ASSOEADR_1         (0x02)
#define ASSOEADR_0         (0x01)

//                                 ASSOEADR1 register:

#define ASSOEADR_15        (0x80)
#define ASSOEADR_14        (0x40)
#define ASSOEADR_13        (0x20)
#define ASSOEADR_12        (0x10)
#define ASSOEADR_11        (0x08)
#define ASSOEADR_10        (0x04)
#define ASSOEADR_9         (0x02)
#define ASSOEADR_8         (0x01)

//                                 ASSOEADR2 register:

#define ASSOEADR_23        (0x80)
#define ASSOEADR_22        (0x40)
#define ASSOEADR_21        (0x20)
#define ASSOEADR_20        (0x10)
#define ASSOEADR_19        (0x08)
#define ASSOEADR_18        (0x04)
#define ASSOEADR_17        (0x02)
#define ASSOEADR_16        (0x01)

//                                 ASSOEADR3 register:

#define ASSOEADR_31        (0x80)
#define ASSOEADR_30        (0x40)
#define ASSOEADR_29        (0x20)
#define ASSOEADR_28        (0x10)
#define ASSOEADR_27        (0x08)
#define ASSOEADR_26        (0x04)
#define ASSOEADR_25        (0x02)
#define ASSOEADR_24        (0x01)

//                                 ASSOEADR4 register:

#define ASSOEADR_39        (0x80)
#define ASSOEADR_38        (0x40)
#define ASSOEADR_37        (0x20)
#define ASSOEADR_36        (0x10)
#define ASSOEADR_35        (0x08)
#define ASSOEADR_34        (0x04)
#define ASSOEADR_33        (0x02)
#define ASSOEADR_32        (0x01)

//                                 ASSOEADR5 register:

#define ASSOEADR_47        (0x80)
#define ASSOEADR_46        (0x40)
#define ASSOEADR_45        (0x20)
#define ASSOEADR_44        (0x10)
#define ASSOEADR_43        (0x08)
#define ASSOEADR_42        (0x04)
#define ASSOEADR_41        (0x02)
#define ASSOEADR_40        (0x01)

//                                 ASSOEADR6 register:

#define ASSOEADR_55        (0x80)
#define ASSOEADR_54        (0x40)
#define ASSOEADR_53        (0x20)
#define ASSOEADR_52        (0x10)
#define ASSOEADR_51        (0x08)
#define ASSOEADR_50        (0x04)
#define ASSOEADR_49        (0x02)
#define ASSOEADR_48        (0x01)

//                                 ASSOEADR7 register:

#define ASSOEADR_63        (0x80)
#define ASSOEADR_62        (0x40)
#define ASSOEADR_61        (0x20)
#define ASSOEADR_60        (0x10)
#define ASSOEADR_59        (0x08)
#define ASSOEADR_58        (0x04)
#define ASSOEADR_57        (0x02)
#define ASSOEADR_56        (0x01)

//                                 ASSOSADR0 register:

#define ASSOSADR_7         (0x80)
#define ASSOSADR_6         (0x40)
#define ASSOSADR_5         (0x20)
#define ASSOSADR_4         (0x10)
#define ASSOSADR_3         (0x08)
#define ASSOSADR_2         (0x04)
#define ASSOSADR_1         (0x02)
#define ASSOSADR_0         (0x01)

//                                 ASSOSADR1 register:

#define ASSOSADR_15        (0x80)
#define ASSOSADR_14        (0x40)
#define ASSOSADR_13        (0x20)
#define ASSOSADR_12        (0x10)
#define ASSOSADR_11        (0x08)
#define ASSOSADR_10        (0x04)
#define ASSOSADR_9         (0x02)
#define ASSOSADR_8         (0x01)

//                                 UPNONCE0 register:

#define UPNONCE_7          (0x80)
#define UPNONCE_6          (0x40)
#define UPNONCE_5          (0x20)
#define UPNONCE_4          (0x10)
#define UPNONCE_3          (0x08)
#define UPNONCE_2          (0x04)
#define UPNONCE_1          (0x02)
#define UPNONCE_0          (0x01)

//                                 UPNONCE1 register:

#define UPNONCE_15         (0x80)
#define UPNONCE_14         (0x40)
#define UPNONCE_13         (0x20)
#define UPNONCE_12         (0x10)
#define UPNONCE_11         (0x08)
#define UPNONCE_10         (0x04)
#define UPNONCE_9          (0x02)
#define UPNONCE_8          (0x01)

//                                 UPNONCE2 register:

#define UPNONCE_23         (0x80)
#define UPNONCE_22         (0x40)
#define UPNONCE_21         (0x20)
#define UPNONCE_20         (0x10)
#define UPNONCE_19         (0x08)
#define UPNONCE_18         (0x04)
#define UPNONCE_17         (0x02)
#define UPNONCE_16         (0x01)

//                                 UPNONCE3 register:

#define UPNONCE_31         (0x80)
#define UPNONCE_30         (0x40)
#define UPNONCE_29         (0x20)
#define UPNONCE_28         (0x10)
#define UPNONCE_27         (0x08)
#define UPNONCE_26         (0x04)
#define UPNONCE_25         (0x02)
#define UPNONCE_24         (0x01)

//                                 UPNONCE4 register:

#define UPNONCE_39         (0x80)
#define UPNONCE_38         (0x40)
#define UPNONCE_37         (0x20)
#define UPNONCE_36         (0x10)
#define UPNONCE_35         (0x08)
#define UPNONCE_34         (0x04)
#define UPNONCE_33         (0x02)
#define UPNONCE_32         (0x01)

//                                 UPNONCE5 register:

#define UPNONCE_47         (0x80)
#define UPNONCE_46         (0x40)
#define UPNONCE_45         (0x20)
#define UPNONCE_44         (0x10)
#define UPNONCE_43         (0x08)
#define UPNONCE_42         (0x04)
#define UPNONCE_41         (0x02)
#define UPNONCE_40         (0x01)

//                                 UPNONCE6 register:

#define UPNONCE_55         (0x80)
#define UPNONCE_54         (0x40)
#define UPNONCE_53         (0x20)
#define UPNONCE_52         (0x10)
#define UPNONCE_51         (0x08)
#define UPNONCE_50         (0x04)
#define UPNONCE_49         (0x02)
#define UPNONCE_48         (0x01)

//                                 UPNONCE7 register:

#define UPNONCE_63         (0x80)
#define UPNONCE_62         (0x40)
#define UPNONCE_61         (0x20)
#define UPNONCE_60         (0x10)
#define UPNONCE_59         (0x08)
#define UPNONCE_58         (0x04)
#define UPNONCE_57         (0x02)
#define UPNONCE_56         (0x01)

//                                 UPNONCE8 register:

#define UPNONCE_71         (0x80)
#define UPNONCE_70         (0x40)
#define UPNONCE_69         (0x20)
#define UPNONCE_68         (0x10)
#define UPNONCE_67         (0x08)
#define UPNONCE_66         (0x04)
#define UPNONCE_65         (0x02)
#define UPNONCE_64         (0x01)

//                                 UPNONCE9 register:

#define UPNONCE_79         (0x80)
#define UPNONCE_78         (0x40)
#define UPNONCE_77         (0x20)
#define UPNONCE_76         (0x10)
#define UPNONCE_75         (0x08)
#define UPNONCE_74         (0x04)
#define UPNONCE_73         (0x02)
#define UPNONCE_72         (0x01)

//                                 UPNONCE10 register:

#define UPNONCE_87         (0x80)
#define UPNONCE_86         (0x40)
#define UPNONCE_85         (0x20)
#define UPNONCE_84         (0x10)
#define UPNONCE_83         (0x08)
#define UPNONCE_82         (0x04)
#define UPNONCE_81         (0x02)
#define UPNONCE_80         (0x01)

//                                 UPNONCE11 register:

#define UPNONCE_95         (0x80)
#define UPNONCE_94         (0x40)
#define UPNONCE_93         (0x20)
#define UPNONCE_92         (0x10)
#define UPNONCE_91         (0x08)
#define UPNONCE_90         (0x04)
#define UPNONCE_89         (0x02)
#define UPNONCE_88         (0x01)

//                                 UPNONCE12 register:

#define UPNONCE_103        (0x80)
#define UPNONCE_102        (0x40)
#define UPNONCE_101        (0x20)
#define UPNONCE_100        (0x10)
#define UPNONCE_99         (0x08)
#define UPNONCE_98         (0x04)
#define UPNONCE_97         (0x02)
#define UPNONCE_96         (0x01)



#define CLEAR_REGISTER     (0x00)


/***************************Public Type Definitions********************************/


typedef struct{
    uint16_t startAddr;
    uint16_t endAddr;
    bool  isRegisterSection;
    bool  isWritable;
}MemorySection;

/***************************Public Data Definitions********************************/

extern const MemorySection  MemMap[MRF24J40_MEM_SECTIONS];

/***************************Public Function Definitions****************************/

MemorySection GetSectionById(uint8_t id);

#endif /* MRF24J40_MEMMAP_H_ */
