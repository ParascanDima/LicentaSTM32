/*
 * ifgsm.c
 *
 *  Created on: 11 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "ifgsm.h"
#include <string.h>
#include "custom_string.h"    /* You can use the custom module to work with strings */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include <stdbool.h>
//#include "uart.h"             /* Include the UART module */
//#include "Timer.h"            /* Include the TIMER module */
//#include "io.h"               /* Include the IO module */

/**************Private Macro Definitions*****************/

#define UNEXPECTED_RSP_MSG_LENGTH   40

#define GSM_RX_BUFF_SIZE            0x64

/**************Private Type Definitions******************/

typedef struct
{
	uint8_t * GSM_Buffer;
	volatile uint8_t   bufWritePosition;

}GSM;

/**************Private Variable Definitions**************/

static uint8_t unexpectRespBuffer[UNEXPECTED_RSP_MSG_LENGTH];

static uint8_t GsmRespBuffer[GSM_RX_BUFF_SIZE];


static GSM GSM_Data = {.GSM_Buffer = GsmRespBuffer, .bufWritePosition = 0};
/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/





/**************Public Function Definitions***************/

void gsmUnexpectRspBufferReset(void){
    CustomClrStr((char*)unexpectRespBuffer);
}

void gsmIntToString( uint16_t num, uint8_t* str){
    CustomIntToString(num, str);
}

uint16_t gsmMessageToINT(uint8_t* string, uint8_t nrofSimbolsToConvert){
    return CustomToINT(string, nrofSimbolsToConvert);
}

uint8_t isEmpty(uint8_t* buffer){
    return isBufferEmpty(buffer);
}



uint8_t gsmCompleteResponseReceived(uint8_t* responseBuffer){
    return FindSubStr(responseBuffer, (uint8_t)strlen((const char*)responseBuffer), (uint8_t*)"\r\n", 2);
}


uint8_t gsmCompareUnexpectRspWith(uint8_t* str){
    return FindSubStr(unexpectRespBuffer, (uint8_t)strlen((const char*)unexpectRespBuffer), str, strlen((const char*)str));
}

void gsmCopyUnexpectResponse(uint8_t* unexpectedResponse){
    gsmUnexpectRspBufferReset();
    (void)strcpy((char*)unexpectRespBuffer, (const char *)unexpectedResponse);
}

void gsmReadUnexpectResponseTo(uint8_t * dest){
    (void)strcpy((char*)dest, (const char *)unexpectRespBuffer);
    gsmUnexpectRspBufferReset();
}

/* --------------------------- GPIO dependent code ---------------------------  */

void gsmRstPullDown(void)
{
    /* Set the pin connected to RST of SIM900 to LOW ("0") */
	HAL_GPIO_WritePin(GSM_RST_GPIO_Port, GSM_RST_Pin, GPIO_PIN_SET);
}

void gsmRstPullUp(void)
{
    /* Set the pin connected to RST of SIM900 to HIGH ("1") */
	HAL_GPIO_WritePin(GSM_RST_GPIO_Port, GSM_RST_Pin, GPIO_PIN_RESET);
}

void gsmPwrKeyOFF(void)
{
    /* Set the pin connected to PWRKEY of SIM900 to LOW ("0") */
	HAL_GPIO_WritePin(GSM_PWRKEY_GPIO_Port, GSM_PWRKEY_Pin, GPIO_PIN_SET);
}

void gsmPwrKeyON(void)
{
    /* Set the pin connected to PWRKEY of SIM900 to HIGH ("1") */
	HAL_GPIO_WritePin(GSM_PWRKEY_GPIO_Port, GSM_PWRKEY_Pin, GPIO_PIN_RESET);
}

/* --------------------------- UART dependent code ---------------------------  */


void gsmTransmit(uint8_t* data){
    /* UART transmit interface */
	HAL_UART_Transmit(&huart6, data, (uint8_t)strlen((const char*)data), 1000);
	HAL_UART_Receive_IT(&huart6, GSM_Data.GSM_Buffer, 1);
}


void gsmStartListening(void)
{
	HAL_UART_Receive_IT(&huart6, &GSM_Data.GSM_Buffer[GSM_Data.bufWritePosition++], 1);
}

void gsmResponseBufferReset(void){
    /* Clear the UART buffer interface */
	 CustomClrStr((char*)GSM_Data.GSM_Buffer);
	 GSM_Data.bufWritePosition = 0;
}


uint8_t* gsmGet_Response(){
    /* Get the UART buffer interface */
	return GsmRespBuffer;
}

uint8_t gsmCompareResponseWith(uint8_t* str){
    /* Verify if "str" string is in UART buffer */
	uint8_t size = (uint8_t)strlen((const char*)str);
	return FindSubStr(GsmRespBuffer, (uint8_t)strlen((const char*)GsmRespBuffer), str, size);
}



/* --------------------------- TIMER dependent code ---------------------------  */

void gsmDelay_ms(uint16_t miliseconds){
    /* The delay function implemented by using timer */
	osDelay(miliseconds);
}


uint8_t gsmCheckTimeout( uint32_t planed_ms ){
	/* This function check if the planed time reached */

	/* Example:

    if (planed_ms < time_quant_count){
        tRsp = FALSE;
    }
    else{
        tRsp = TRUE;
    }

	 * */
	uint8_t tRsp;
	if (planed_ms < HAL_GetTick())
	{
		tRsp = false;
	}
	else{
		tRsp = true;
	}
	return tRsp;
}


uint32_t gsmPlaneTout(uint16_t planed_ms){
    /* This function get the counter value of type uint64 that is incremented every 1 ms and add to this
     * "planed_ms" */
	return (HAL_GetTick() + (uint32_t)planed_ms);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(huart, &GSM_Data.GSM_Buffer[GSM_Data.bufWritePosition], 1);
	GSM_Data.bufWritePosition++;
}

