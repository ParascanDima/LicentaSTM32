/*
 * GSM_cnf.h
 *
 *  Created on: 13 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef GSM_CNF_H_
#define GSM_CNF_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#define MY_NUMBER               (uint8_t*)"+37368047277"
#define SERVER_HOST             (uint8_t*)"217.26.174.207"
#define SERVER_CONNECTION_PORT  (uint8_t*)"351"

#define GSM_COMMAND_START_WATERING                                 0x01
#define GSM_COMMAND_STOP_WATERING                                  0x02
#define GSM_COMMAND_COLLECTING_DATA                                0x03

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

uint8_t GSM_IsCommand(void);
uint8_t GSM_ListenToServerCommands(void);

#endif /* GSM_CNF_H_ */
