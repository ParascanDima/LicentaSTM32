/*
 * mrf24j40ma_pinout.h
 *
 *  Created on: 16 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef MRF24J40MA_PINOUT_H_
#define MRF24J40MA_PINOUT_H_


/***************************Imports*************************************************/



/***************************Public Macro Definitions********************************/



/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

void MRF24J40_ChipSelectPullDown(void);
void MRF24J40_ChipSelectPullUp(void);
void MRF24J40_WakePinPullUp(void);
void MRF24J40_WakePinPullDown(void);
void MRF24J40_RstPinPullUp(void);
void MRF24J40_RstPinPullDown(void);
void MRF24J40_PinOutInit(void);
void MRF24J40_InterruptEnable(void);
void MRF24J40_InterruptDisable(void);
void MRF24J40_ClearInterruptFlag(void);
void MRF24J40_Disable(void);

#endif /* MRF24J40MA_PINOUT_H_ */
