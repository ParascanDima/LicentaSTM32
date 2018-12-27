/*
 * lgdp4524_pinout.h
 *
 *  Created on: 16 џэт. 2018 у.
 *      Author: Dumitru
 */

#ifndef LGDP4524_PINOUT_H_
#define LGDP4524_PINOUT_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#ifndef RST_PIN
#define RST_PIN           RST_Pin
#endif
#ifndef RST_PORT
#define RST_PORT          RST_GPIO_Port
#endif

/*Check if pin interface is used, not FSMC*/

//                     1-____________     ____________
//                     0-            |___|
#define PULSE_LOW(PIN)   PullDown##PIN(); PullUp##PIN()
//                     1-             ____
//                     0-____________|    |____________
#define PULSE_HIGH(PIN)  PullUp##PIN(); PullDown##PIN()

#ifndef FSMC_IS_USED

#define LCD_INPUT_BUS    (0x00)
#define LCD_OUTPUT_BUS   (0x01)


/*  Configuration of control pins  */

#define CS_PIN            CS_Pin
#define CS_PORT           CS_GPIO_Port

#define RS_PIN            RS_Pin
#define RS_PORT           RS_GPIO_Port

#define WR_PIN            WR_Pin
#define WR_PORT           WR_GPIO_Port

#define RD_PIN            RD_Pin
#define RD_PORT           RD_GPIO_Port


/*  Configuration of data pins  */

#define DB0_PIN           DB0_Pin
#define DB0_PORT          DB0_GPIO_Port

#define DB1_PIN           DB1_Pin
#define DB1_PORT          DB1_GPIO_Port

#define DB2_PIN           DB2_Pin
#define DB2_PORT          DB2_GPIO_Port

#define DB3_PIN           DB3_Pin
#define DB3_PORT          DB3_GPIO_Port

#define DB4_PIN           DB4_Pin
#define DB4_PORT          DB4_GPIO_Port

#define DB5_PIN           DB5_Pin
#define DB5_PORT          DB5_GPIO_Port

#define DB6_PIN           DB6_Pin
#define DB6_PORT          DB6_GPIO_Port

#define DB7_PIN           DB7_Pin
#define DB7_PORT          DB7_GPIO_Port

/*  Configuration of touch pins  */

#define X_PLUS_PIN        DB6_PIN
#define X_PLUS_PORT       DB6_PORT

#define X_MINUS_PIN       RS_PIN
#define X_MINUS_PORT      RS_PORT

#define Y_PLUS_PIN        WR_PIN
#define Y_PLUS_PORT       WR_PORT

#define Y_MINUS_PIN       DB7_PIN
#define Y_MINUS_PORT      DB7_PORT
#endif

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

#ifndef FSMC_IS_USED
void PullDownWR(void);
void PullUpWR(void);
void PullDownCS(void);
void PullUpCS(void);
void PullDownRS(void);
void PullUpRS(void);
void PullDownRD(void);
void PullUpRD(void);

void TrigWrite(void);

void SetDataDirectionRegister(uint8_t direction);
void SetPinAsInput(volatile void* selectedPort, uint16_t selectedPin);
void SetPinAsOutput(volatile void* selectedPort, uint16_t selectedPin);
void SetLow(volatile void* selectedPort, uint16_t selectedPins);
void SetHigh(volatile void* selectedPort, uint16_t selectedPins);
void SetDataToParallelPort(uint16_t data);
uint8_t GetDataFromParallelPort(void);
#else
void FSMC_Write_Cmd(uint16_t cmd);
void FSMC_Write_Data(uint16_t data);
uint16_t FSMC_Read_Data(void);
#endif

void PullDownRST(void);
void PullUpRST(void);

void LGDP4524_PinoutInit(void);


#endif /* LGDP4524_PINOUT_H_ */
