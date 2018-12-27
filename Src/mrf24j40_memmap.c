/*
 * mrf24j40_memmap.c
 *
 *  Created on: 25 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "mrf24j40_memmap.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Declarations**************/




/**************Public Variable Declarations***************/

const MemorySection  MemMap[MRF24J40_MEM_SECTIONS] =
{

 /* startAddr                         |           endAddr                    |  isRegisterSection  |   isWritable    */
 { LOW_CONTROL_REGISTERS_START_ADDR,       LOW_CONTROL_REGISTERS_END_ADDR,           true,               true        },

 { TX_NORMAL_FIFO_START_ADDR,              TX_NORMAL_FIFO_END_ADDR,                  false,              true        },

 { TX_BEACON_FIFO_START_ADDR,              TX_BEACON_FIFO_END_ADDR,                  false,              true        },

 { TX_GTS1_FIFO_START_ADDR,                TX_GTS1_FIFO_END_ADDR,                    false,              true        },

 { TX_GTS2_FIFO_START_ADDR,                TX_GTS2_FIFO_END_ADDR,                    false,              true        },

 { HIGH_CONTROL_REGISTERS_START_ADDR,      HIGH_CONTROL_REGISTERS_END_ADDR,          true,               true        },

 { SECURITY_KEY_FIFO_START_ADDR,           SECURITY_KEY_FIFO_END_ADDR,               false,              true        },

 { RESERVED_START_ADDR,                    RESERVED_END_ADDR,                        false,              false       },

 { RX_FIFO_START_ADDR,                     RX_FIFO_END_ADDR,                         false,              false       }

};

/**************Private Function Declarations**************/



/**************Public Function Declarations***************/

MemorySection GetSectionById(uint8_t id){
    return MemMap[id];
}
