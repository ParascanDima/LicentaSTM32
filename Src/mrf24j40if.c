/*
 * mrf24j40if.c
 *
 *  Created on: 16 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "mrf24j40if.h"
#include "time.h"
#include "main.h"
#include "stm32f4xx_hal.h"
//#include "SPI/spi.h"               /* Include the spi header */
//#include "Timer/Timer.h"           /* Include the timer header */


/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/




/**************Public Variable Definitions***************/

extern SPI_HandleTypeDef hspi1;

/**************Private Function Definitions**************/





/**************Public Function Definitions***************/

/* ---------------------------- SPI dependent code ---------------------------- */

void MRF24J40IF_SpiTransmit(uint8_t v) // write 1 byte to SPI
{
	uint8_t data = v;
    /* Interface for transmit data through SPI */
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

uint8_t MRF24J40IF_SpiReceive(void) // read 1 byte from SPI
{
	uint8_t data = 0;
    /* Interface for receive data through SPI */
	HAL_SPI_Receive(&hspi1, &data, 1, 1000);

	return data;
}




/* ---------------------------- Timer dependent code ---------------------------- */

void MRF24J40IF_Delay_ms(uint16_t miliseconds){
    /* Delay function (simple delay based on onChip timer is not compatible with OS_Delay) */
	HAL_Delay(miliseconds);
}


uint32_t MRF24J40IF_ElapsedTimeSince(uint32_t time){
    /* "time" represent the saved Timer tick or SYS tick and returning the difference between actual value of
     * SYS tick (timer tick) and "time" parameter */
	return (uint32_t)(HAL_GetTick() - time);
}

uint32_t MRF24J40IF_GetSysMilliseconds(void){
    /* This function returning milliseconds converted value of SYS tick */
	return HAL_GetTick();
}

