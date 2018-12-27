/*
 * atcmd.c
 *
 *  Created on: 11 окт. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "atcmd.h"
#include "ifgsm.h"
#include "custom_string.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/




/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/





/**************Public Function Definitions***************/


void gsmAT_CPOWD(void){
    gsmTransmit((uint8_t*)"AT+CPOWD=1\r\n");
}


void gsmAT_CGATT(uint8_t param){
    uint8_t buffer[13] = "AT+CGATT=";
    uint8_t paramStr[2] = "";

    CustomIntToString((uint16_t)param, paramStr);

    (void)strcat((char*)buffer, (char*)paramStr);
    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}


void gsmAT_CSTT(uint8_t* apn){
    uint8_t buffer[42] = "AT+CSTT=\"";

    (void)strcat((char*)buffer, (char*)apn);
    (void)strcat((char*)buffer, "\"\r\n");

    gsmTransmit(buffer);
}


void gsmAT_CIICR(void){
    gsmTransmit((uint8_t*)"AT+CIICR\r\n");
}


void gsmAT_CIFSR(void){
    gsmTransmit((uint8_t*)"AT+CIFSR\r\n");
}


void gsmAT_CIPMUX(uint8_t conType){
    uint8_t buffer[13] = "AT+CIPMUX=";
    uint8_t typeStr[2] = "";

    CustomIntToString(conType, typeStr);

    (void)strcat((char*)buffer, (char*)typeStr);
    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}


void gsmAT_CIPSTART(uint8_t* host, uint8_t* port)
{
    uint8_t buffer[44] = "AT+CIPSTART=\"TCP\",\"";

    (void)strcat((char*)buffer, (char*)host);
    (void)strcat((char*)buffer, "\",\"");
    (void)strcat((char*)buffer, (char*)port);
    (void)strcat((char*)buffer, "\"\r\n");
    gsmTransmit(buffer);
}


void gsmAT_CIPSHUT(void){
    gsmTransmit((uint8_t*)"AT+CIPSHUT\r\n");
}


void gsmAT_HTTPINIT(void){
    gsmTransmit((uint8_t*)"AT+HTTPINIT\r\n");
}

void gsmAT_HTTPPARA(uint8_t HTTPParamTag, uint8_t* HTTPParmValue){

    uint8_t buffer[80] = "AT+HTTPPARA=\"";

    switch(HTTPParamTag){
    case GSM_HTTP_PARAM_CID:
        (void)strcat((char*)buffer, "CID");
        break;

    case GSM_HTTP_PARAM_URL:
        (void)strcat((char*)buffer, "URL");
        break;

    case GSM_HTTP_PARAM_UA:
        (void)strcat((char*)buffer, "UA");
        break;

    case GSM_HTTP_PARAM_PROIP:
        (void)strcat((char*)buffer, "PROIP");
        break;

    case GSM_HTTP_PARAM_PROPORT:
        (void)strcat((char*)buffer, "PROPORT");
        break;

    case GSM_HTTP_PARAM_REDIR:
        (void)strcat((char*)buffer, "REDIR");
        break;

    case GSM_HTTP_PARAM_BREAK:
        (void)strcat((char*)buffer, "BREAK");
        break;

    case GSM_HTTP_PARAM_BREAKEND:
        (void)strcat((char*)buffer, "BREAKEND");
        break;

    case GSM_HTTP_PARAM_TIMEOUT:
        (void)strcat((char*)buffer, "TIMEOUT");
        break;

    case GSM_HTTP_PARAM_CONTENT:
        (void)strcat((char*)buffer, "CONTENT");
        break;

    default:
        return;
    }

    (void)strcat((char*)buffer, "\",\"");
    (void)strcat((char*)buffer, (char*)HTTPParmValue);
    (void)strcat((char*)buffer, "\"\r\n");

    gsmTransmit(buffer);
}

void gsmAT_HTTPDATA(uint16_t nrOfBytes, uint16_t latencyTime){

    uint8_t buffer[30] = "AT+HTTPDATA=";
    uint8_t tempStr[16] = "";

    CustomIntToString(nrOfBytes, tempStr);
    (void)strcat((char*)buffer, (char*)tempStr);

    (void)strcat((char*)buffer, ",");

    CustomIntToString(latencyTime, tempStr);
    (void)strcat((char*)buffer, (char*)tempStr);

    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}

void gsmAT_HTTPACTION(uint8_t method){
    uint8_t buffer[18] = "AT+HTTPACTION=";
    uint8_t methodStr[2] = "";

    CustomIntToString(method, methodStr);
    (void)strcat((char*)buffer, (char*)methodStr);

    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}

void gsmAT_HTTPTERM(void){

    gsmTransmit((uint8_t*)"AT+HTTPTERM\r\n");
}

void gsmATH0(void){

    gsmTransmit((uint8_t*)"ATH0\r\n");
}

void gsmATD(uint8_t* phoneNumber){
    uint8_t buffer[18] = "ATD";

    (void)strcat((char*)buffer, (char*)phoneNumber);
    (void)strcat((char*)buffer, ";\r\n");
    gsmTransmit(buffer);
}

void gsmAT_SAPBR(uint8_t cmd_type, uint8_t cid, uint8_t* ConParamTag, uint8_t* ConParamValue){
    uint8_t buffer[77] = "AT+SAPBR=";
    uint8_t cmdTypeStr[2] = "";
    uint8_t cidStr[2] = "";

    CustomIntToString((uint16_t)cmd_type, cmdTypeStr);
    CustomIntToString((uint16_t)cid, cidStr);

    (void)strcat((char*)buffer, (char*)cmdTypeStr);
    (void)strcat((char*)buffer, ",");
    (void)strcat((char*)buffer, (char*)cidStr);
    if (cmd_type != 1){
        (void)strcat((char*)buffer, ",\"");
        (void)strcat((char*)buffer, (char*)ConParamTag);
        (void)strcat((char*)buffer, "\",\"");
        (void)strcat((char*)buffer, (char*)ConParamValue);
        (void)strcat((char*)buffer, "\"");
    }
    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}

void gsmAT_IPR(uint16_t baud){
    uint8_t buffer[13] = "AT+IPR=";
    uint8_t baudStr[6] = "";

    CustomIntToString(baud, baudStr);

    (void)strcat((char*)buffer, (char*)baudStr);
    (void)strcat((char*)buffer, "\r\n");

    gsmTransmit(buffer);
}

void gsmCheckNetworkRegistration(void){
    gsmTransmit((uint8_t*)"AT+CREG?");
}

void gsmCheckGprsConnection(void){
    gsmTransmit((uint8_t*)"AT+CGATT?");
}

void gsmAT_CPIN(uint16_t pinCode){
    uint8_t buffer[15] = "AT+CPIN=";
    uint8_t pinCodeStr[5] = "";

    CustomIntToString(pinCode, pinCodeStr);

    (void)strcat((char*)buffer, (char*)pinCodeStr);
    (void)strcat((char*)buffer, "\r\n");


    gsmTransmit(buffer);
}

