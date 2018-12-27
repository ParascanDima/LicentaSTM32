/*
 * mrf24j40if.h
 *
 *  Created on: 16 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef MRF24J40IF_H_
#define MRF24J40IF_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#define MILLISECONDS(x)        x
#define MRF24J40_TIMEOUT_TIME  MILLISECONDS(30)

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/
void     MRF24J40IF_SpiTransmit(uint8_t v);
uint8_t  MRF24J40IF_SpiReceive(void);

void     MRF24J40IF_Delay_ms(uint16_t miliseconds);
uint32_t MRF24J40IF_GetSysMilliseconds(void);
uint32_t MRF24J40IF_ElapsedTimeSince(uint32_t time);

#endif /* MRF24J40IF_H_ */
