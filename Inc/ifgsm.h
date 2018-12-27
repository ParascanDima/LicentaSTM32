/*
 * ifgsm.h
 *
 *  Created on: 11 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef IFGSM_H_
#define IFGSM_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#define gsmHttpSendData(data)   gsmTransmit(data)
#define gsmCompareMessageWith   gsmCompareResponseWith

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

void     gsmRstPullDown(void);

void     gsmRstPullUp(void);

void     gsmPwrKeyOFF(void);

void     gsmPwrKeyON(void);

void     gsmTransmit(uint8_t* data);

void     gsmResponseBufferReset(void);

void     gsmUnexpectRspBufferReset(void);

void     gsmDelay_ms(uint16_t miliseconds);

void     gsmCopyUnexpectResponse(uint8_t* unexpectedResponse);

void     gsmReadUnexpectResponseTo(uint8_t * dest);

void     gsmIntToString( uint16_t num, uint8_t* str);


uint8_t  gsmCompleteResponseReceived(uint8_t* responseBuffer);

uint8_t  isEmpty(uint8_t* buffer);

uint8_t* gsmGet_Response(void);

uint8_t  gsmCompareResponseWith(uint8_t* str);

uint8_t  gsmCompareUnexpectRspWith(uint8_t* str);

uint8_t  gsmCheckTimeout( uint32_t planed_ms );


uint16_t gsmMessageToINT(uint8_t* string, uint8_t nrofSimbolsToConvert);


uint32_t gsmPlaneTout(uint16_t planed_ms);


void gsmStartListening(void);

#endif /* IFGSM_H_ */
