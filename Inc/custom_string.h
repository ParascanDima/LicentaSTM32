/*
 * custom_string.h
 *
 *  Created on: 8 мая 2017 г.
 *      Author: Dumitru
 */

#ifndef CUSTOM_STRING_H_
#define CUSTOM_STRING_H_


/***************************Imports*************************************************/
#include <stdint.h>
#include <string.h>
//#include "custom_defs.h"

/***************************Public Macro Definitions********************************/



/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

void CustomClrStr(char* buf);
void CustomIntToString( uint16_t num, uint8_t* str);
uint16_t CustomToINT(uint8_t* string, uint8_t nrofSimbolsToConvert);
uint8_t FindSubStr(uint8_t* source, uint8_t sourcelength, uint8_t* str, uint8_t strlength);
uint8_t isBufferEmpty(uint8_t* buffer);
uint8_t* readBytes(uint8_t* dstPtr, uint8_t* srcPtr, uint16_t count);


#endif /* CUSTOM_STRING_H_ */
