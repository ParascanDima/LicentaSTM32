/*
 * lgdp4524if.h
 *
 *  Created on: 1 θών. 2018 γ.
 *      Author: Dumitru
 */

#ifndef _LGDP4524IF_H_
#define _LGDP4524IF_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#define SWAP(type, i, j) {type t = i; i = j; j = t;}


#ifdef FSMC_IS_USED
#if !defined(ADDR_CMD) || !defined(ADDR_DATA)
#define ADDR_CMD  *(volatile uint8_t*)0x60000000
#define ADDR_DATA *(volatile uint8_t*)0x60010000
#else
#error "Memory addresses for FSMC are already defined"
#endif
#endif

/***************************Public Type Definitions********************************/

#define fontdatatype uint8_t const

/***************************Public Data Definitions********************************/

extern fontdatatype SevenSegNumFont[2004];
extern fontdatatype BigFont[3044];
extern fontdatatype SmallFont[1144];

extern uint16_t imageBleati[];

/***************************Public Function Definitions****************************/

void LGDP4524_Delay_ms(uint16_t miliseconds);


#endif /* _LGDP4524IF_H_ */
