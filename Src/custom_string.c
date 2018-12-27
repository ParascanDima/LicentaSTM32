/*
 * custom_string.c
 *
 *  Created on: 8 мая 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "custom_string.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/




/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/


uint16_t U8PowerU8(uint8_t a, uint8_t n){
    uint16_t val = (uint16_t)a;
    uint8_t i;

    if(!n){
        return 1;
    }

    for (i = 0; i < (n-1); i++){
        val *= a;
    }

    return val;
}


/**************Public Function Definitions***************/

void CustomIntToString( uint16_t num, uint8_t* str){
    int8_t len;
    int8_t i;

    if( num < 10 ){
        len = 1;
    }
    else{
        if( num < 100 ){
            len = 2;
        }
        else{
            if( num < 1000 ){
                len = 3;
            }

            else {
                if( num < 10000 ){
                    len = 4;
                }
                else len = 5;
            }
        }
    }

    for ( i = len - 1 ; i > -1; i-- ){
        str[i] = (num % 10) + '0';
        num /= 10;
    }
    str[len] = '\0';
}


uint16_t CustomToINT(uint8_t* string, uint8_t nrofSimbolsToConvert){
    uint8_t i = 0;
    uint16_t rspVal = 0;

    for (i = 0; i < nrofSimbolsToConvert; i++ ){
        rspVal += (string[i] - 0x30)*(100/(U8PowerU8(10, i)));
    }

    return rspVal;
}

void CustomClrStr(char* buf){
    unsigned char j;
    size_t buf_len =  strlen(buf);

    for( j = 0; j < buf_len; j++)
        {
            buf[j] = 1;
        }
}

uint8_t FindSubStr(uint8_t* source, uint8_t sourcelength, uint8_t* str, uint8_t strlength){
    uint8_t i = sourcelength;
    uint8_t foundSymbols = 0;

    if (source == NULL)
        return 0;

    while(i){

        if ( (i < strlength) && (foundSymbols == 0) ){
            return 0;
        }

        if(foundSymbols < strlength){
            if (str[foundSymbols] == source[sourcelength - i]){
                foundSymbols++;
            }
            else{
                foundSymbols = 0;
            }
        }
        else{
            return 1;
        }

        i--;
    }
    if (foundSymbols != strlength){
        return 0;
    }
    else{
        return 1;
    }
}

uint8_t isBufferEmpty(uint8_t* buffer){
    uint8_t rsp;

    if (strlen((const char*)buffer) != 0){
        rsp = 0;
    }
    else{
        rsp = 1;
    }

    return rsp;
    //return strlen((const char*)buffer)?0:1;
}

uint8_t* readBytes(uint8_t* dstPtr, uint8_t* srcPtr, uint16_t count)
{
    while(count--){
        *dstPtr++ = *srcPtr++;
    }

    return srcPtr;
}
