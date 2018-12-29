/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "lgdp4524.h"
#include "GSM.h"
#include "mrf24j40.h"
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osSemaphoreId zigbeeSemaHandle;
osSemaphoreId gsmSemaHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void ZigBeeTask(void const * argument);
void GsmTask(void const * argument);
void DisplayTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of zigbeeSema */
  osSemaphoreDef(zigbeeSema);
  zigbeeSemaHandle = osSemaphoreCreate(osSemaphore(zigbeeSema), 1);

  /* definition and creation of gsmSema */
  osSemaphoreDef(gsmSema);
  gsmSemaHandle = osSemaphoreCreate(osSemaphore(gsmSema), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, ZigBeeTask, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, GsmTask, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, DisplayTask, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* ZigBeeTask function */
void ZigBeeTask(void const * argument)
{
  /* USER CODE BEGIN ZigBeeTask */
	RadioInit();
	RadioInitP2P();
	/* Infinite loop */
	for(;;)
	{
		if (osOK == osSemaphoreWait(zigbeeSemaHandle, 10))
		{
			RadioTXPacket();
		}
		HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
		osDelay(500);
	}
  /* USER CODE END ZigBeeTask */
}

/* GsmTask function */
void GsmTask(void const * argument)
{
  /* USER CODE BEGIN GsmTask */
//	uint8_t beacon[5] = "Here\r";
	uint8_t reqType = 0;
	uint8_t pendingRsp = false;
	GSM_Init();
	if (GSM_HttpGet((uint8_t*)"217.26.174.207:350/saveip/") == GSM_HTTP_RESPONSE_OK){
		GSM_StartServerConnection(SERVER_HOST, SERVER_CONNECTION_PORT);
	}
	/* Infinite loop */
	for(;;)
	{
		switch (GSM_ListenToServerCommands())
		{
		case GSM_COMMAND_START_WATERING:
			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
			MRF24J40_ToSend((uint8_t*)"Start watering", 15);
			osSemaphoreRelease(zigbeeSemaHandle);
			pendingRsp = true;
			reqType = 1;
			break;
		case GSM_COMMAND_COLLECTING_DATA:
			HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
			MRF24J40_ToSend((uint8_t*)"Start collecting data", 22);
			osSemaphoreRelease(zigbeeSemaHandle);
			pendingRsp = true;
			reqType = 2;
			break;
		default:
			break;
		}
		if ((pendingRsp == true)/* && (osOK == osSemaphoreWait(gsmSemaHandle, 0))*/)
		{
			if (reqType == 1)
			{
				GSM_TcpSend((uint8_t*)"Watering started", 16);
				reqType = 0;
			}
			else if (reqType == 2)
			{
				GSM_TcpSend((uint8_t*)"Collecting started", 18);
				reqType = 0;
			}
		}
	}
  /* USER CODE END GsmTask */
}

/* DisplayTask function */
void DisplayTask(void const * argument)
{
  /* USER CODE BEGIN DisplayTask */
	ZigBeeStateType zigbeeState = MRF24J40_GetState();
	uint8_t* zigbeeStateStr[2] = {(uint8_t*)"UNINITIALIZED", (uint8_t*)"INITIALIZED"};

	uint8_t gsmState = Get_eGsmState();
	uint8_t* gsmStateStr[8] = {(uint8_t*)"enIDLE", (uint8_t*)"enRDY", (uint8_t*)"enCallReady", (uint8_t*)"enOK", (uint8_t*)"enReset",
			(uint8_t*)"enCalling", (uint8_t*)"enNoSIM", (uint8_t*)"enUnreachable"};

	uint8_t gsmGprsState = Get_eGPRSState();
	uint8_t* gsmGprsStateStr[10] = {(uint8_t*)"enIPInitial", (uint8_t*)"enIPstart", (uint8_t*)"enIPConfig", (uint8_t*)"enIPGprsAct",
			(uint8_t*)"enIPStatus", (uint8_t*)"enIPprocessing", (uint8_t*)"enConnectOk", (uint8_t*)"enTcpClosing",
			(uint8_t*)"enTcpClosed", (uint8_t*)"enPDPdeactivated"};

	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
	osDelay(10);

	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	osDelay(10);
	LCD_LGDP4524_Init(enLandscape);
	SetFont((uint8_t*)SmallFont);

	ClrScr();
	FillScr(255, 255, 255);
	SetBrushColor(0, 0, 0);
	SetBackColor(255, 255, 255, 255);
	Print((uint8_t*)"ZIGBEE STATE:", LEFT, 50, 0);
	Print((uint8_t*)"GSM STATE:", LEFT, 90, 0);
	Print((uint8_t*)"GPRS STATE:", LEFT, 105, 0);

	Print(zigbeeStateStr[zigbeeState], 104, 50, 0);
	Print(gsmStateStr[gsmState], 80, 90, 0);
	Print(gsmGprsStateStr[gsmGprsState], 88, 105, 0);
  /* Infinite loop */
  for(;;)
  {
	  if (zigbeeState != MRF24J40_GetState())
	  {
			SetBrushColor(255, 255, 255);
			Print(zigbeeStateStr[zigbeeState], 104, 50, 0);
			zigbeeState = MRF24J40_GetState();
			SetBrushColor(0, 0, 0);
			Print(zigbeeStateStr[zigbeeState], 104, 50, 0);
		}
		if (gsmState != Get_eGsmState())
		{
			SetBrushColor(255, 255, 255);
			Print(gsmStateStr[gsmState], 80, 90, 0);
			gsmState = Get_eGsmState();
			SetBrushColor(0, 0, 0);
			Print(gsmStateStr[gsmState], 80, 90, 0);
		}
		if (gsmGprsState != Get_eGPRSState())
		{
			SetBrushColor(255, 255, 255);
			Print(gsmGprsStateStr[gsmGprsState], 88, 105, 0);
			gsmGprsState = Get_eGPRSState();
			SetBrushColor(0, 0, 0);
			Print(gsmGprsStateStr[gsmGprsState], 88, 105, 0);
		}
		osDelay(50);
  }
  /* USER CODE END DisplayTask */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
