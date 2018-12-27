/*
 * lgdp4524_memmap.h
 *
 *  Created on: 13 џэт. 2018 у.
 *      Author: Dumitru
 */

#ifndef LGDP4524_CMD_H_
#define LGDP4524_CMD_H_


/***************************Imports*************************************************/

#include "lgdp4524_pinout.h"

/***************************Public Macro Definitions********************************/

/*  Instruction indexes based on LGDP4524 Datasheet (in "doc" folder of LGDP4524 module)  */

#define StartOscillation           0x00
#define DrvOutputCtrl              0x01
#define DrivingWaveformCtrl        0x02
#define EntryMode                  0x03
#define ResizeCtrl                 0x04
#define DisplayCtrl_1              0x07
#define DisplayCtrl_2              0x08
#define DisplayCtrl_3              0x09
#define FrameCycleCtrl             0x0B
#define ExtDisplayIfCtrl_2         0x0C

#define PwrCtrl_1                  0x10
#define PwrCtrl_2                  0x11
#define PwrCtrl_3                  0x12
#define PwrCtrl_4                  0x13
#define PwrCtrl_5                  0x14

#define RamAddrSet                 0x21
#define GramWriteData              0x22

#define yControl_0                 0x30
#define yControl_1                 0x31
#define yControl_2                 0x32
#define yControl_3                 0x33
#define yControl_4                 0x34
#define yControl_5                 0x35
#define yControl_6                 0x36
#define yControl_7                 0x37
#define yControl_8                 0x38
#define yControl_9                 0x39
#define yControl_A                 0x3A
#define yControl_B                 0x3B
#define yControl_C                 0x3C
#define yControl_D                 0x3D
#define yControl_E                 0x3E
#define yControl_F                 0x3F


#define GateScanPos                0x40
#define VerticalScrollCtrl         0x41
#define FirstScreenDrivePos        0x42
#define SecondScreenDrivePos       0x43
#define HorizontalRamAddrPos       0x44
#define VerticalRamAddrPos         0x45

#define EpromCtrl_1                0x60
#define EpromCtrl_2                0x61


#define TestReg_1                  0x71
#define TestReg_2                  0x72



/* ------------------------------------------ Bits of registers definition ------------------------------------------ */

/* --------------------- Driver Output Control (R01h) --------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
#define VSPL                      (uint16_t)0x4000         /* BIT 14 */
#define HSPL                      (uint16_t)0x2000         /* BIT 13 */
#define DPL                       (uint16_t)0x1000         /* BIT 12 */

#define EPL                       (uint16_t)0x0800         /* BIT 11 */
#define SM                        (uint16_t)0x0400         /* BIT 10 */
#define GS                        (uint16_t)0x0200         /* BIT 9  */
#define SS                        (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define NL_4                      (uint16_t)0x0010         /* BIT 4  */

#define NL_3                      (uint16_t)0x0008         /* BIT 3  */
#define NL_2                      (uint16_t)0x0004         /* BIT 2  */
#define NL_1                      (uint16_t)0x0002         /* BIT 1  */
#define NL_0                      (uint16_t)0x0001         /* BIT 0  */


/* --------------------- LCD Driving Vaweform Control (R02h) --------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

#define FLD_1                     (uint16_t)0x0800         /* BIT 11 */
#define FLD_0                     (uint16_t)0x0400         /* BIT 10 */
#define B_C                       (uint16_t)0x0200         /* BIT 9  */
#define EOR                       (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define NW_5                      (uint16_t)0x0020         /* BIT 5  */
#define NW_4                      (uint16_t)0x0010         /* BIT 4  */

#define NW_3                      (uint16_t)0x0008         /* BIT 3  */
#define NW_2                      (uint16_t)0x0004         /* BIT 2  */
#define NW_1                      (uint16_t)0x0002         /* BIT 1  */
#define NW_0                      (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------ Entry Mode (R03h) ------------------------------ */


#define TRI                      (uint16_t)0x8000          /* BIT 15 */
#define DFM                      (uint16_t)0x4000          /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
#define BGR                       (uint16_t)0x1000         /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define ID__1                     (uint16_t)0x0020         /* BIT 5  */
#define ID__0                     (uint16_t)0x0010         /* BIT 4  */

#define AM                        (uint16_t)0x0008         /* BIT 3  */
//#define ZERO                      (uint16_t)0x0004       /* BIT 2  */
//#define ZERO                      (uint16_t)0x0002       /* BIT 1  */
//#define ZERO                      (uint16_t)0x0001       /* BIT 0  */


/* ---------------------------- Resize Control (R04h) ---------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
#define RVC_1                      (uint16_t)0x0200        /* BIT 9  */
#define RVC_0                      (uint16_t)0x0100        /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define RCH_1                     (uint16_t)0x0020         /* BIT 5  */
#define RCH_0                     (uint16_t)0x0010         /* BIT 4  */

#define AM                        (uint16_t)0x0008         /* BIT 3  */
//#define ZERO                      (uint16_t)0x0004       /* BIT 2  */
//#define ZERO                      (uint16_t)0x0002       /* BIT 1  */
//#define ZERO                      (uint16_t)0x0001       /* BIT 0  */


/* --------------------------- Display Control 1 (R07h) -------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
#define PTS_2                     (uint16_t)0x2000         /* BIT 13 */
#define PTS_1                     (uint16_t)0x1000         /* BIT 12 */

#define PTS_0                     (uint16_t)0x0800         /* BIT 11 */
#define VLE_1                     (uint16_t)0x0400         /* BIT 10 */
#define VLE_0                     (uint16_t)0x0200         /* BIT 9  */
#define SPT                       (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define GON                       (uint16_t)0x0020         /* BIT 5  */
#define DTE                       (uint16_t)0x0010         /* BIT 4  */

#define CL                        (uint16_t)0x0008         /* BIT 3  */
#define REV                       (uint16_t)0x0004         /* BIT 2  */
#define D_1                       (uint16_t)0x0002         /* BIT 1  */
#define D_0                       (uint16_t)0x0001         /* BIT 0  */


/* --------------------------- Display Control 2 (R08h) -------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

#define FP_3                      (uint16_t)0x0800         /* BIT 11 */
#define FP_2                      (uint16_t)0x0400         /* BIT 10 */
#define FP_1                      (uint16_t)0x0200         /* BIT 9  */
#define FP_0                      (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

#define BP_3                      (uint16_t)0x0008         /* BIT 3  */
#define BP_2                      (uint16_t)0x0004         /* BIT 2  */
#define BP_1                      (uint16_t)0x0002         /* BIT 1  */
#define BP_0                      (uint16_t)0x0001         /* BIT 0  */


/* --------------------------- Display Control 3 (R09h) -------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define PTG_1                     (uint16_t)0x0020         /* BIT 5  */
#define PTG_0                     (uint16_t)0x0010         /* BIT 4  */

#define ISC_3                     (uint16_t)0x0008         /* BIT 3  */
#define ISC_2                     (uint16_t)0x0004         /* BIT 2  */
#define ISC_1                     (uint16_t)0x0002         /* BIT 1  */
#define ISC_0                     (uint16_t)0x0001         /* BIT 0  */


/* ------------------------- Frame Cycle Control 3 (R0Bh) ------------------------ */


#define NO_1                      (uint16_t)0x8000         /* BIT 15 */
#define NO_0                      (uint16_t)0x4000         /* BIT 14 */
#define SDT_1                     (uint16_t)0x2000         /* BIT 13 */
#define SDT_0                     (uint16_t)0x1000         /* BIT 12 */

#define EQ_1                      (uint16_t)0x0800         /* BIT 11 */
#define EQ_0                      (uint16_t)0x0400         /* BIT 10 */
#define DIV_1                     (uint16_t)0x0200         /* BIT 9  */
#define DIV_0                     (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define RTN_6                     (uint16_t)0x0040         /* BIT 6  */
#define RTN_5                     (uint16_t)0x0020         /* BIT 5  */
#define RTN_4                     (uint16_t)0x0010         /* BIT 4  */

#define RTN_3                     (uint16_t)0x0008         /* BIT 3  */
#define RTN_2                     (uint16_t)0x0004         /* BIT 2  */
#define RTN_1                     (uint16_t)0x0002         /* BIT 1  */
#define RTN_0                     (uint16_t)0x0001         /* BIT 0  */


/* ---------------- External Display Interface Control 1 (R0Ch) ------------------ */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
#define RM                        (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
#define DM_1                      (uint16_t)0x0020         /* BIT 5  */
#define DM_0                      (uint16_t)0x0010         /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
//#define ZERO                      (uint16_t)0x0004       /* BIT 2  */
#define RIM_1                     (uint16_t)0x0002         /* BIT 1  */
#define RIM_0                     (uint16_t)0x0001         /* BIT 0  */



/* ---------------------------- Power Control 1 (R10h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
#define SAP_2                     (uint16_t)0x4000         /* BIT 14 */
#define SAP_1                     (uint16_t)0x2000         /* BIT 13 */
#define SAP_0                     (uint16_t)0x1000         /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define BT_2                      (uint16_t)0x0400         /* BIT 10 */
#define BT_1                      (uint16_t)0x0200         /* BIT 9  */
#define BT_0                      (uint16_t)0x0100         /* BIT 8  */

#define DUAL                      (uint16_t)0x0080         /* BIT 7  */
#define AP_2                      (uint16_t)0x0040         /* BIT 6  */
#define AP_1                      (uint16_t)0x0020         /* BIT 5  */
#define AP_0                      (uint16_t)0x0010         /* BIT 4  */

#define STB                       (uint16_t)0x0008         /* BIT 3  */
#define DK                        (uint16_t)0x0004         /* BIT 2  */
#define SLP                       (uint16_t)0x0002         /* BIT 1  */
#define DSTB                      (uint16_t)0x0001         /* BIT 0  */

/* ---------------------------- Power Control 2 (R11h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define DC1_2                     (uint16_t)0x0400         /* BIT 10 */
#define DC1_1                     (uint16_t)0x0200         /* BIT 9  */
#define DC1_0                     (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define DC0_2                     (uint16_t)0x0040         /* BIT 6  */
#define DC0_1                     (uint16_t)0x0020         /* BIT 5  */
#define DC0_0                     (uint16_t)0x0010         /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define VC_2                      (uint16_t)0x0004         /* BIT 2  */
#define VC_1                      (uint16_t)0x0002         /* BIT 1  */
#define VC_0                      (uint16_t)0x0001         /* BIT 0  */


/* ---------------------------- Power Control 3 (R12h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define PON                       (uint16_t)0x0010         /* BIT 4  */

#define VRH_3                     (uint16_t)0x0008         /* BIT 3  */
#define VRH_2                     (uint16_t)0x0004         /* BIT 2  */
#define VRH_1                     (uint16_t)0x0002         /* BIT 1  */
#define VRH_0                     (uint16_t)0x0001         /* BIT 0  */

/* ---------------------------- Power Control 4 (R13h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
#define VCOMG                     (uint16_t)0x2000         /* BIT 13 */
#define VDV_4                     (uint16_t)0x1000         /* BIT 12 */

#define VDV_3                     (uint16_t)0x0800         /* BIT 11 */
#define VDV_2                     (uint16_t)0x0400         /* BIT 10 */
#define VDV_1                     (uint16_t)0x0200         /* BIT 9  */
#define VDV_0                     (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define VCM_6                     (uint16_t)0x0040         /* BIT 6  */
#define VCM_5                     (uint16_t)0x0020         /* BIT 5  */
#define VCM_4                     (uint16_t)0x0010         /* BIT 4  */

#define VCM_3                     (uint16_t)0x0008         /* BIT 3  */
#define VCM_2                     (uint16_t)0x0004         /* BIT 2  */
#define VCM_1                     (uint16_t)0x0002         /* BIT 1  */
#define VCM_0                     (uint16_t)0x0001         /* BIT 0  */


/* ---------------------------- Power Control 5 (R14h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define RI_2                      (uint16_t)0x0400         /* BIT 10 */
#define RI_1                      (uint16_t)0x0200         /* BIT 9  */
#define RI_0                      (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define RV_2                      (uint16_t)0x0040         /* BIT 6  */
#define RV_1                      (uint16_t)0x0020         /* BIT 5  */
#define RV_0                      (uint16_t)0x0010         /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
//#define ZERO                      (uint16_t)0x0004       /* BIT 2  */
#define L_BIAS_ENB                (uint16_t)0x0002         /* BIT 1  */
//#define RESERVED                  (uint16_t)0x0001       /* BIT 0  */


/* ---------------------------- RAM Address Set (R21h) --------------------------- */


#define AD_15                     (uint16_t)0x8000         /* BIT 15 */
#define AD_14                     (uint16_t)0x4000         /* BIT 14 */
#define AD_13                     (uint16_t)0x2000         /* BIT 13 */
#define AD_12                     (uint16_t)0x1000         /* BIT 12 */

#define AD_11                     (uint16_t)0x0800         /* BIT 11 */
#define AD_10                     (uint16_t)0x0400         /* BIT 10 */
#define AD_9                      (uint16_t)0x0200         /* BIT 9  */
#define AD_8                      (uint16_t)0x0100         /* BIT 8  */

#define AD_7                      (uint16_t)0x0080         /* BIT 7  */
#define AD_6                      (uint16_t)0x0040         /* BIT 6  */
#define AD_5                      (uint16_t)0x0020         /* BIT 5  */
#define AD_4                      (uint16_t)0x0010         /* BIT 4  */

#define AD_3                      (uint16_t)0x0008         /* BIT 3  */
#define AD_2                      (uint16_t)0x0004         /* BIT 2  */
#define AD_1                      (uint16_t)0x0002         /* BIT 1  */
#define AD_0                      (uint16_t)0x0001         /* BIT 0  */


/* --------------------------- Write data to GRAM (R22h) ------------------------- */


#define WD_15                     (uint16_t)0x8000         /* BIT 15 */
#define WD_14                     (uint16_t)0x4000         /* BIT 14 */
#define WD_13                     (uint16_t)0x2000         /* BIT 13 */
#define WD_12                     (uint16_t)0x1000         /* BIT 12 */

#define WD_11                     (uint16_t)0x0800         /* BIT 11 */
#define WD_10                     (uint16_t)0x0400         /* BIT 10 */
#define WD_9                      (uint16_t)0x0200         /* BIT 9  */
#define WD_8                      (uint16_t)0x0100         /* BIT 8  */

#define WD_7                      (uint16_t)0x0080         /* BIT 7  */
#define WD_6                      (uint16_t)0x0040         /* BIT 6  */
#define WD_5                      (uint16_t)0x0020         /* BIT 5  */
#define WD_4                      (uint16_t)0x0010         /* BIT 4  */

#define WD_3                      (uint16_t)0x0008         /* BIT 3  */
#define WD_2                      (uint16_t)0x0004         /* BIT 2  */
#define WD_1                      (uint16_t)0x0002         /* BIT 1  */
#define WD_0                      (uint16_t)0x0001         /* BIT 0  */


/* --------------------------- Read data from GRAM (R22h) ------------------------- */


#define RD_15                     (uint16_t)0x8000         /* BIT 15 */
#define RD_14                     (uint16_t)0x4000         /* BIT 14 */
#define RD_13                     (uint16_t)0x2000         /* BIT 13 */
#define RD_12                     (uint16_t)0x1000         /* BIT 12 */

#define RD_11                     (uint16_t)0x0800         /* BIT 11 */
#define RD_10                     (uint16_t)0x0400         /* BIT 10 */
#define RD_9                      (uint16_t)0x0200         /* BIT 9  */
#define RD_8                      (uint16_t)0x0100         /* BIT 8  */

#define RD_7                      (uint16_t)0x0080         /* BIT 7  */
#define RD_6                      (uint16_t)0x0040         /* BIT 6  */
#define RD_5                      (uint16_t)0x0020         /* BIT 5  */
#define RD_4                      (uint16_t)0x0010         /* BIT 4  */

#define RD_3                      (uint16_t)0x0008         /* BIT 3  */
#define RD_2                      (uint16_t)0x0004         /* BIT 2  */
#define RD_1                      (uint16_t)0x0002         /* BIT 1  */
#define RD_0                      (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 0 (R30h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKP1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKP1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKP1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKP0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKP0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKP0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 1 (R31h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKP3_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKP3_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKP3_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKP2_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKP2_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKP2_0                    (uint16_t)0x0001         /* BIT 0  */

/* ------------------------------- y-Control 2 (R32h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKP5_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKP5_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKP5_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKP4_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKP4_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKP4_0                    (uint16_t)0x0001         /* BIT 0  */

/* ------------------------------- y-Control 3 (R33h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PRP1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PRP1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PRP1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PRP0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PRP0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PRP0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 4 (R34h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKN1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKN1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKN1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKN0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKN0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKN0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 5 (R35h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKN3_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKN3_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKN3_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKN2_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKN2_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKN2_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 6 (R36h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PKN5_2                    (uint16_t)0x0400         /* BIT 10 */
#define PKN5_1                    (uint16_t)0x0200         /* BIT 9  */
#define PKN5_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PKN4_2                    (uint16_t)0x0004         /* BIT 2  */
#define PKN4_1                    (uint16_t)0x0002         /* BIT 1  */
#define PKN4_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 7 (R37h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PRN1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PRN1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PRN1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PRN0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PRN0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PRN0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 8 (R38h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
#define VRP1_4                    (uint16_t)0x1000         /* BIT 12 */

#define VRP1_3                    (uint16_t)0x0800         /* BIT 11 */
#define VRP1_2                    (uint16_t)0x0400         /* BIT 10 */
#define VRP1_1                    (uint16_t)0x0200         /* BIT 9  */
#define VRP1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define VRP0_4                    (uint16_t)0x0010         /* BIT 4  */

#define VRP0_3                    (uint16_t)0x0008         /* BIT 3  */
#define VRP0_2                    (uint16_t)0x0004         /* BIT 2  */
#define VRP0_1                    (uint16_t)0x0002         /* BIT 1  */
#define VRP0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control 9 (R39h) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
#define VRN1_4                    (uint16_t)0x1000         /* BIT 12 */

#define VRN1_3                    (uint16_t)0x0800         /* BIT 11 */
#define VRN1_2                    (uint16_t)0x0400         /* BIT 10 */
#define VRN1_1                    (uint16_t)0x0200         /* BIT 9  */
#define VRN1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define VRN0_4                    (uint16_t)0x0010         /* BIT 4  */

#define VRN0_3                    (uint16_t)0x0008         /* BIT 3  */
#define VRN0_2                    (uint16_t)0x0004         /* BIT 2  */
#define VRN0_1                    (uint16_t)0x0002         /* BIT 1  */
#define VRN0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control A (R3Ah) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PFP1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PFP1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PFP1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PFP0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PFP0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PFP0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control B (R3Bh) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PFP3_2                    (uint16_t)0x0400         /* BIT 10 */
#define PFP3_1                    (uint16_t)0x0200         /* BIT 9  */
#define PFP3_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PFP2_2                    (uint16_t)0x0004         /* BIT 2  */
#define PFP2_1                    (uint16_t)0x0002         /* BIT 1  */
#define PFP2_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control C (R3Ch) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PFN1_2                    (uint16_t)0x0400         /* BIT 10 */
#define PFN1_1                    (uint16_t)0x0200         /* BIT 9  */
#define PFN1_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PFN0_2                    (uint16_t)0x0004         /* BIT 2  */
#define PFN0_1                    (uint16_t)0x0002         /* BIT 1  */
#define PFN0_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control D (R3Dh) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
#define PFN3_2                    (uint16_t)0x0400         /* BIT 10 */
#define PFN3_1                    (uint16_t)0x0200         /* BIT 9  */
#define PFN3_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PFN2_2                    (uint16_t)0x0004         /* BIT 2  */
#define PFN2_1                    (uint16_t)0x0002         /* BIT 1  */
#define PFN2_0                    (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control E (R3Eh) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define RESERVED                  (uint16_t)0x0400       /* BIT 10 */
//#define RESERVED                  (uint16_t)0x0200       /* BIT 9  */
//#define RESERVED                  (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PMP_2                     (uint16_t)0x0004         /* BIT 2  */
#define PMP_1                     (uint16_t)0x0002         /* BIT 1  */
#define PMP_0                     (uint16_t)0x0001         /* BIT 0  */


/* ------------------------------- y-Control F (R3Fh) ----------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
//#define ZERO                      (uint16_t)0x0010       /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define PMN_2                     (uint16_t)0x0004         /* BIT 2  */
#define PMN_1                     (uint16_t)0x0002         /* BIT 1  */
#define PMN_0                     (uint16_t)0x0001         /* BIT 0  */


/* ---------------------------- Gate Scan Position (R40h) ------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define SCN_4                     (uint16_t)0x0010         /* BIT 4  */

#define SCN_3                     (uint16_t)0x0008         /* BIT 3  */
#define SCN_2                     (uint16_t)0x0004         /* BIT 2  */
#define SCN_1                     (uint16_t)0x0002         /* BIT 1  */
#define SCN_0                     (uint16_t)0x0001         /* BIT 0  */


/* -------------------------- Vertical Scroll Control (R41h) ---------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

#define VL_7                      (uint16_t)0x0080         /* BIT 7  */
#define VL_6                      (uint16_t)0x0040         /* BIT 6  */
#define VL_5                      (uint16_t)0x0020         /* BIT 5  */
#define VL_4                      (uint16_t)0x0010         /* BIT 4  */

#define VL_3                      (uint16_t)0x0008         /* BIT 3  */
#define VL_2                      (uint16_t)0x0004         /* BIT 2  */
#define VL_1                      (uint16_t)0x0002         /* BIT 1  */
#define VL_0                      (uint16_t)0x0001         /* BIT 0  */


/* ------------------------- 1st-Screen Drive Position (R42h) --------------------- */


#define SE1_7                     (uint16_t)0x8000         /* BIT 15 */
#define SE1_6                     (uint16_t)0x4000         /* BIT 14 */
#define SE1_5                     (uint16_t)0x2000         /* BIT 13 */
#define SE1_4                     (uint16_t)0x1000         /* BIT 12 */

#define SE1_3                     (uint16_t)0x0800         /* BIT 11 */
#define SE1_2                     (uint16_t)0x0400         /* BIT 10 */
#define SE1_1                     (uint16_t)0x0200         /* BIT 9  */
#define SE1_0                     (uint16_t)0x0100         /* BIT 8  */

#define SS1_7                     (uint16_t)0x0080         /* BIT 7  */
#define SS1_6                     (uint16_t)0x0040         /* BIT 6  */
#define SS1_5                     (uint16_t)0x0020         /* BIT 5  */
#define SS1_4                     (uint16_t)0x0010         /* BIT 4  */

#define SS1_3                     (uint16_t)0x0008         /* BIT 3  */
#define SS1_2                     (uint16_t)0x0004         /* BIT 2  */
#define SS1_1                     (uint16_t)0x0002         /* BIT 1  */
#define SS1_0                     (uint16_t)0x0001         /* BIT 0  */


/* ------------------------- 2nd-Screen Drive Position (R43h) --------------------- */


#define SE2_7                     (uint16_t)0x8000         /* BIT 15 */
#define SE2_6                     (uint16_t)0x4000         /* BIT 14 */
#define SE2_5                     (uint16_t)0x2000         /* BIT 13 */
#define SE2_4                     (uint16_t)0x1000         /* BIT 12 */

#define SE2_3                     (uint16_t)0x0800         /* BIT 11 */
#define SE2_2                     (uint16_t)0x0400         /* BIT 10 */
#define SE2_1                     (uint16_t)0x0200         /* BIT 9  */
#define SE2_0                     (uint16_t)0x0100         /* BIT 8  */

#define SS2_7                     (uint16_t)0x0080         /* BIT 7  */
#define SS2_6                     (uint16_t)0x0040         /* BIT 6  */
#define SS2_5                     (uint16_t)0x0020         /* BIT 5  */
#define SS2_4                     (uint16_t)0x0010         /* BIT 4  */

#define SS2_3                     (uint16_t)0x0008         /* BIT 3  */
#define SS2_2                     (uint16_t)0x0004         /* BIT 2  */
#define SS2_1                     (uint16_t)0x0002         /* BIT 1  */
#define SS2_0                     (uint16_t)0x0001         /* BIT 0  */


/* --------------------- Horizontal RAM Address Position (R44h) ------------------- */


#define HEA_7                     (uint16_t)0x8000         /* BIT 15 */
#define HEA_6                     (uint16_t)0x4000         /* BIT 14 */
#define HEA_5                     (uint16_t)0x2000         /* BIT 13 */
#define HEA_4                     (uint16_t)0x1000         /* BIT 12 */

#define HEA_3                     (uint16_t)0x0800         /* BIT 11 */
#define HEA_2                     (uint16_t)0x0400         /* BIT 10 */
#define HEA_1                     (uint16_t)0x0200         /* BIT 9  */
#define HEA_0                     (uint16_t)0x0100         /* BIT 8  */

#define HSA_7                     (uint16_t)0x0080         /* BIT 7  */
#define HSA_6                     (uint16_t)0x0040         /* BIT 6  */
#define HSA_5                     (uint16_t)0x0020         /* BIT 5  */
#define HSA_4                     (uint16_t)0x0010         /* BIT 4  */

#define HSA_3                     (uint16_t)0x0008         /* BIT 3  */
#define HSA_2                     (uint16_t)0x0004         /* BIT 2  */
#define HSA_1                     (uint16_t)0x0002         /* BIT 1  */
#define HSA_0                     (uint16_t)0x0001         /* BIT 0  */


/* ---------------------- Vertical RAM Address Position (R45h) -------------------- */


#define VEA_7                     (uint16_t)0x8000         /* BIT 15 */
#define VEA_6                     (uint16_t)0x4000         /* BIT 14 */
#define VEA_5                     (uint16_t)0x2000         /* BIT 13 */
#define VEA_4                     (uint16_t)0x1000         /* BIT 12 */

#define VEA_3                     (uint16_t)0x0800         /* BIT 11 */
#define VEA_2                     (uint16_t)0x0400         /* BIT 10 */
#define VEA_1                     (uint16_t)0x0200         /* BIT 9  */
#define VEA_0                     (uint16_t)0x0100         /* BIT 8  */

#define VSA_7                     (uint16_t)0x0080         /* BIT 7  */
#define VSA_6                     (uint16_t)0x0040         /* BIT 6  */
#define VSA_5                     (uint16_t)0x0020         /* BIT 5  */
#define VSA_4                     (uint16_t)0x0010         /* BIT 4  */

#define VSA_3                     (uint16_t)0x0008         /* BIT 3  */
#define VSA_2                     (uint16_t)0x0004         /* BIT 2  */
#define VSA_1                     (uint16_t)0x0002         /* BIT 1  */
#define VSA_0                     (uint16_t)0x0001         /* BIT 0  */


/* ----------------------------- EPROM Control 1 (R60h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
#define POR                       (uint16_t)0x2000         /* BIT 13 */
#define EVPP                      (uint16_t)0x1000         /* BIT 12 */

#define PPROG                     (uint16_t)0x0800         /* BIT 11 */
#define PWE                       (uint16_t)0x0400         /* BIT 10 */
#define PA_1                      (uint16_t)0x0200         /* BIT 9  */
#define PA_0                      (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define PDIN_6                    (uint16_t)0x0040         /* BIT 6  */
#define PDIN_5                    (uint16_t)0x0020         /* BIT 5  */
#define PDIN_4                    (uint16_t)0x0010         /* BIT 4  */

#define PDIN_3                    (uint16_t)0x0008         /* BIT 3  */
#define PDIN_2                    (uint16_t)0x0004         /* BIT 2  */
#define PDIN_1                    (uint16_t)0x0002         /* BIT 1  */
#define PDIN_0                    (uint16_t)0x0001         /* BIT 0  */


/* ----------------------------- EPROM Control 2 (R61h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
//#define ZERO                      (uint16_t)0x0100       /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define AUTOWE                    (uint16_t)0x0010         /* BIT 4  */

#define RA_1                      (uint16_t)0x0008         /* BIT 3  */
#define RA_0                      (uint16_t)0x0004         /* BIT 2  */
#define VCMSEL_1                  (uint16_t)0x0002         /* BIT 1  */
#define VCMSEL_0                  (uint16_t)0x0001         /* BIT 0  */


/* ----------------------------- Test Register 1 (R71h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
//#define ZERO                      (uint16_t)0x1000       /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
#define TDLY_1                    (uint16_t)0x0200         /* BIT 9  */
#define TDLY_0                    (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
#define T8CL                      (uint16_t)0x0040         /* BIT 6  */
#define TPOL_1                    (uint16_t)0x0020         /* BIT 5  */
#define TPOL_0                    (uint16_t)0x0010         /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
#define TMEM                      (uint16_t)0x0004         /* BIT 2  */
#define TOSC                      (uint16_t)0x0002         /* BIT 1  */
#define TFN                       (uint16_t)0x0001         /* BIT 0  */


/* ----------------------------- Test Register 2 (R72h) --------------------------- */


//#define ZERO                      (uint16_t)0x8000       /* BIT 15 */
//#define ZERO                      (uint16_t)0x4000       /* BIT 14 */
//#define ZERO                      (uint16_t)0x2000       /* BIT 13 */
#define REGULPD                   (uint16_t)0x1000         /* BIT 12 */

//#define ZERO                      (uint16_t)0x0800       /* BIT 11 */
//#define ZERO                      (uint16_t)0x0400       /* BIT 10 */
//#define ZERO                      (uint16_t)0x0200       /* BIT 9  */
#define S_HIZ                     (uint16_t)0x0100         /* BIT 8  */

//#define ZERO                      (uint16_t)0x0080       /* BIT 7  */
//#define ZERO                      (uint16_t)0x0040       /* BIT 6  */
//#define ZERO                      (uint16_t)0x0020       /* BIT 5  */
#define MVCOML                    (uint16_t)0x0010         /* BIT 4  */

//#define ZERO                      (uint16_t)0x0008       /* BIT 3  */
//#define ZERO                      (uint16_t)0x0004       /* BIT 2  */
#define MVCI                      (uint16_t)0x0002         /* BIT 1  */
//#define ZERO                      (uint16_t)0x0001       /* BIT 0  */

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/


#endif /* LGDP4524_CMD_H_ */
