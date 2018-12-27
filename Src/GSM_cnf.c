/*
 * GSM_cnf.c
 *
 *  Created on: 13 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "GSM.h"
#include "ifgsm.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/




/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/





/**************Public Function Definitions***************/


uint8_t GSM_IsCommand(void){
    uint8_t tRsp = 0;
    uint8_t * buffer = gsmGet_Response();

    if(buffer[0] != 1){
        tRsp = gsmCompareMessageWith((uint8_t*)"\1\r\1\n");
    }
    return tRsp;
}

uint8_t GSM_ListenToServerCommands(void){
    uint8_t tRsp = 0;
    if(GSM_IsCommand()){
        if (gsmCompareMessageWith((uint8_t*)"Start watering"))
        {
            tRsp = GSM_COMMAND_START_WATERING;
            gsmResponseBufferReset();
            return tRsp;
        }
        else{
            if(gsmCompareMessageWith((uint8_t*)"Start collecting data")){
                tRsp = GSM_COMMAND_COLLECTING_DATA;
                gsmResponseBufferReset();
            }
        }
    }
    return tRsp;
}
