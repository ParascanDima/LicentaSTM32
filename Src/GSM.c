/*
 * GSM.c
 *
 *  Created on: 30 апр. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "GSM.h"
#include "atcmd.h"
#include "ifgsm.h"
#include <string.h>

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/

static GSM_STATE eGsmState = enIDLE;
static GSM_GPRS_STATE eGprsState = enPDPdeactivated;
static GSM_COMM_STATE eGsmCommState = enCommIdle;

/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/


void Set_eGsmState(GSM_STATE state){
    eGsmState = state;
}

void Set_eGprsState(GSM_GPRS_STATE state){
    eGprsState = state;
}

void Set_eGsmCommState(GSM_COMM_STATE state){
	eGsmCommState = state;
}

void hardGsmReset(void){
    //Get value at STATUS pin
    if (Get_eGsmState() != enIDLE/* && STATUS_pin is high*/){
    	if (enPDPdeactivated != GSM_GetSimGprsState())
    	{
    		GSM_StopGprsConnection();
    	}
        GSM_PowerDown();
        gsmDelay_ms(4000);
    }
    gsmRstPullDown();
    gsmDelay_ms(200);
    gsmRstPullUp();
    gsmPwrKeyOFF();
    gsmDelay_ms(1000);
    gsmPwrKeyON();
    gsmDelay_ms(2000);
    Set_eGsmState(enIDLE);
}


/*MAIN FUNCTION TO CONNECT TO SERVER */



/**************Public Function Definitions***************/


GSM_STATE Get_eGsmState(void){
    return eGsmState;
}

GSM_GPRS_STATE Get_eGPRSState(void){
    return eGprsState;
}

GSM_COMM_STATE Get_eGsmCommState(void){
    return eGsmCommState;
}

uint8_t GSM_ReceiveAtCommandResponse(uint16_t timeout, uint8_t* expectedResponse, uint8_t isStateChanging, uint8_t state, uint8_t isRspNeeded){
    uint32_t _timeout = 0;
    uint8_t * buffer = gsmGet_Response();

    _timeout = gsmPlaneTout(timeout);
    while(gsmCheckTimeout(_timeout)){
        if (gsmCompareResponseWith(expectedResponse)){
            if (isStateChanging == GSM_GSM_STATE_CHANGES){
                Set_eGsmState((GSM_STATE)state);
            }
            else{
                if (isStateChanging == GSM_GPRS_STATE_CHANGES){
                    Set_eGprsState((GSM_GPRS_STATE)state);
                }
            }
            if(!isRspNeeded){
                gsmResponseBufferReset();
            }
            return GSM_OK;
        }
        else{
            if(gsmCompareResponseWith((uint8_t*)"ERROR")){
                gsmResponseBufferReset();
                return GSM_ERROR;
            }
        }
    }
    if (!isEmpty(buffer)){
        gsmCopyUnexpectResponse(buffer);
        if(!isRspNeeded){
            gsmResponseBufferReset();
        }
    }
    return GSM_TIMEOUT;
}

uint8_t GSM_CheckInit(void){
    uint8_t tRsp;

    tRsp = GSM_ReceiveAtCommandResponse(100, (uint8_t*)"RDY", GSM_GSM_STATE_CHANGES, (uint8_t)enRDY, GSM_RESPONSE_SAVE_NEEDED);
    if (tRsp == GSM_OK)
    {
        tRsp = GSM_ReceiveAtCommandResponse(100, (uint8_t*)"+CPIN: READY", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_RESPONSE_SAVE_NEEDED);
        if (tRsp == GSM_OK){
            tRsp = GSM_ReceiveAtCommandResponse(100, (uint8_t*)"+CFUN: 1", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
        }
        else{
            if(tRsp != GSM_ERROR){
                if (gsmCompareUnexpectRspWith((uint8_t*)"+CPIN: SIM PIN")){
                    gsmUnexpectRspBufferReset();
                    tRsp = GSM_ENTER_PIN;
                }
                else{
                    if (gsmCompareUnexpectRspWith((uint8_t*)"+CPIN: NOT INSERTED"))
                    {
                        gsmUnexpectRspBufferReset();
                        tRsp = GSM_INSERT_SIM;
                    }
                }
            }
        }
    }
    return tRsp;
}

uint8_t GSM_ReceiveCallResponse(void){

    uint32_t timeout = 0;
    uint8_t tRsp;


    timeout = gsmPlaneTout(2000);
    while(gsmCheckTimeout(timeout)){
        if (gsmCompareResponseWith((uint8_t*)"OK")){
            gsmResponseBufferReset();
            while(Get_eGsmState() == enCalling){
                if (gsmCompareResponseWith((uint8_t*)"NO DIALTONE")){
                    gsmResponseBufferReset();
                    Set_eGsmState(enCallReady);
                    return GSM_CALL_NO_DIALTONE;
                }
                else{
                    if (gsmCompareResponseWith((uint8_t*)"BUSY")){
                        gsmResponseBufferReset();
                        Set_eGsmState(enCallReady);
                        return GSM_CALL_BUSY;
                    }
                    else{
                        if (gsmCompareResponseWith((uint8_t*)"NO ANSWER")){
                            gsmResponseBufferReset();
                            Set_eGsmState(enCallReady);
                            return GSM_CALL_NO_ANSWER;
                        }
                        else{
                            if (gsmCompareResponseWith((uint8_t*)"NO CARRIER")){
                                gsmResponseBufferReset();
                                Set_eGsmState(enCallReady);
                                return GSM_CALL_NO_CARRIER;
                            }
                        }
                    }
                }
            }
            return GSM_CALL_OK;
        }
    }
    gsmResponseBufferReset();
    tRsp = GSM_TIMEOUT;

    return tRsp;
}



GsmHttp_Response GSM_GetHTTPResponseCode(uint8_t method){
    uint8_t tRsp;
    GsmHttp_Response httpRsp = GSM_HTTP_RESPONSE_NETWORK_ERROR;
    uint8_t _methodString[2] = "";
    uint8_t expectedRsp[16] = "+HTTPACTION:";
    uint8_t expectedRspIndex = 0;

    gsmIntToString((uint16_t)method, _methodString);

    strcat((char*)expectedRsp, (char*)_methodString);            /* The expected string is "+HTTPACTION:X,YYY,Z */

    uint8_t * buffer = gsmGet_Response();


    tRsp = GSM_ReceiveAtCommandResponse(HTTP_METHOD_TIMEOUT, expectedRsp, GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_RESPONSE_SAVE_NEEDED);
    if(tRsp == GSM_OK){
        expectedRspIndex = (uint8_t)((uint8_t*)strstr((const char*)buffer, (const char*)expectedRsp) - buffer);
        while(!gsmCompleteResponseReceived(&buffer[expectedRspIndex]));
        httpRsp = gsmMessageToINT(&buffer[expectedRspIndex+14], 3);
        gsmResponseBufferReset();
    }

    return httpRsp;
}


GSM_GPRS_STATE GSM_GetSimGprsState(void){

    uint8_t tRsp;
    GSM_GPRS_STATE state = enPDPdeactivated;
    uint8_t expectedRsp[25] = "STATUS:";
    uint8_t expectedRspIndex = 0;

    uint8_t * buffer = gsmGet_Response();

    tRsp = GSM_ReceiveAtCommandResponse(1000, expectedRsp, GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_RESPONSE_SAVE_NEEDED);
    if(tRsp == GSM_OK){
        expectedRspIndex = (uint8_t)((uint8_t*)strstr((const char*)buffer, (const char*)expectedRsp) - buffer);
        while(!gsmCompleteResponseReceived(&buffer[expectedRspIndex]));
        if(gsmCompareResponseWith((uint8_t*)"IP INITIAL"))
        {
        	state = enIPInitial;
        }
        else if(gsmCompareResponseWith((uint8_t*)"IP START"))
        {
        	state = enIPstart;
        }
        else if(gsmCompareResponseWith((uint8_t*)"IP CONFIG"))
        {
        	state = enIPConfig;
        }
        else if(gsmCompareResponseWith((uint8_t*)"IP GPRSACT"))
        {
        	state = enIPGprsAct;
        }
        else if(gsmCompareResponseWith((uint8_t*)"IP STATUS"))
        {
        	state = enIPprocessing;
        }
        else if(gsmCompareResponseWith((uint8_t*)"TCP CONNECTING"))
        {
        	state = enIPprocessing;
        }
        else if(gsmCompareResponseWith((uint8_t*)"CONNECT OK"))
        {
        	state = enIPprocessing;
        }
        else if(gsmCompareResponseWith((uint8_t*)"TCP CLOSING"))
        {
        	state = enTcpClosing;
        }
        else if(gsmCompareResponseWith((uint8_t*)"TCP CLOSED"))
        {
        	state = enTcpClosed;
        }
        else if(gsmCompareResponseWith((uint8_t*)"PDP DEACT"))
        {
        	state = enPDPdeactivated;
        }
        else
        {
        	state = enPDPdeactivated;
        }
        gsmResponseBufferReset();
        Set_eGprsState(state);
    }

    return state;
}


uint8_t CheckGsmPersistance(void){

	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmTransmit((uint8_t*)"AT\r\n");

    retVal = GSM_ReceiveAtCommandResponse(50, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_SetBaudRate(uint16_t baud){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_IPR(baud);

    retVal = GSM_ReceiveAtCommandResponse(200, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_PowerDown(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CPOWD();

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_GSM_STATE_CHANGES, (uint8_t)enIDLE, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_EnterPinCode(uint16_t pinCode){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CPIN(pinCode);

    retVal = GSM_ReceiveAtCommandResponse(200, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_CallNumber(uint8_t* phoneNumber){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmATD(phoneNumber);

    Set_eGsmState(enCalling);

    retVal = GSM_ReceiveCallResponse();
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_AttachToGPRS(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CGATT(1);

    retVal = GSM_ReceiveAtCommandResponse(6000, (uint8_t*)"OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enIPInitial, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_DetachToGPRS(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CGATT(0);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enPDPdeactivated, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_SetupAPN(uint8_t* apn){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CSTT(apn);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enIPstart, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_GprsSingleConnectionMode(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CIPMUX(0);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_StartGPRS(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CIICR();

    retVal = GSM_ReceiveAtCommandResponse(6000, (uint8_t*)"OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enIPConfig, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_GetLocalIP(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CIFSR();

    retVal = GSM_ReceiveAtCommandResponse(5000, (uint8_t*)"10.12.", GSM_GPRS_STATE_CHANGES, (uint8_t)enIPStatus, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_GprsShutDown(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CIPSHUT();

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"SHUT OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enPDPdeactivated, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_TcpSendMode(uint8_t mode){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_CIPQSEND(mode);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_ConnectToServer(uint8_t* host, uint8_t* port){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
	Set_eGprsState(enIPprocessing);
    gsmAT_CIPSTART(host, port);

    retVal = GSM_ReceiveAtCommandResponse(4000, (uint8_t*)"CONNECT OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enConnectOk, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_TcpSend(uint8_t* data, uint16_t dataLength){
	uint8_t retVal;

    Set_eGsmCommState(enCommBusy);
    gsmAT_CIPSEND(dataLength);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)">", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    if (retVal == GSM_OK)
    {
        gsmTcpSendData(data);
        retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"SEND OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    }
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_InitHTTP(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_HTTPINIT();

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_SetHttpParameters(uint8_t HTTPParamTag, uint8_t* HTTPParmValue){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_HTTPPARA(HTTPParamTag, HTTPParmValue);

    retVal = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_SetHTTPDataToTransfer(uint8_t* postData, uint16_t nrOfBytes, uint16_t latencyTime){
    uint8_t tRsp = GSM_ERROR;

	Set_eGsmCommState(enCommBusy);
    gsmAT_HTTPDATA(nrOfBytes, latencyTime);

    tRsp = GSM_ReceiveAtCommandResponse(1000, (uint8_t*)"DOWNLOAD", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    if(tRsp == GSM_OK){
        gsmHttpSendData(postData);
        tRsp = GSM_ReceiveAtCommandResponse(latencyTime, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    }
    Set_eGsmCommState(enCommIdle);
    return tRsp;
}


uint8_t GSM_SetBearerParameters( uint8_t* ConParamTag, uint8_t* ConParamValue){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_SAPBR(3, 1, ConParamTag, ConParamValue);

    retVal = GSM_ReceiveAtCommandResponse(500, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_OpenBearer(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_SAPBR(1, 1, NULL, NULL);

    retVal = GSM_ReceiveAtCommandResponse(6000, (uint8_t*)"OK", GSM_GPRS_STATE_CHANGES, (uint8_t)enIPStatus, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_HttpMethodAction(uint8_t method){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_HTTPACTION(method);

    retVal = GSM_GetHTTPResponseCode(method);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}


uint8_t GSM_HTTPTerminateService(void){
	uint8_t retVal;

	Set_eGsmCommState(enCommBusy);
    gsmAT_HTTPTERM();

    retVal = GSM_ReceiveAtCommandResponse(3000, (uint8_t*)"OK", GSM_NO_STATE_CHANGES, GSM_NO_STATE_CHANGES, GSM_NO_RESPONSE_SAVE_NEEDED);
    Set_eGsmCommState(enCommIdle);
    return retVal;
}



void GSM_Init(void)
{
    uint8_t tries = 0;
    uint8_t response;
    uint8_t incorrectPIN = 0;

    gsmStartListening();
    while (Get_eGsmState() != enOK && Get_eGsmState() != enNoSIM && Get_eGsmState() != enUnreachable){

        if (tries == MAX_TRIES){
            Set_eGsmState(enUnreachable);
            break;
        }

        hardGsmReset();
        response = GSM_CheckInit();
        if (response == GSM_OK){
            response = GSM_ReceiveAtCommandResponse(8000, (uint8_t*)"Call Ready", GSM_GSM_STATE_CHANGES, (uint8_t)enCallReady, GSM_NO_RESPONSE_SAVE_NEEDED);
            if(response == GSM_OK){
                response = GSM_SetBaudRate(9600);
                if(response == GSM_OK){
                    Set_eGsmState(enOK);
                    GSM_ActivateGprs();
                }
            }
        }
        else{
            if(response == GSM_ENTER_PIN){
                if (incorrectPIN == 1){
                    break;
                }
                response = GSM_EnterPinCode(DEFAULT_PIN_CODE);
                if (response == GSM_ERROR){
                    incorrectPIN++;
                }
            }
            else{
                if (response == GSM_INSERT_SIM){
                    Set_eGsmState(enNoSIM);
                    break;
                }
            }
        }

        if (response == GSM_TIMEOUT){
            tries++;
        }
    }
}


void GSM_ServerSocketConnection(uint8_t* ip_addr, uint8_t* port){
    uint8_t resp = GSM_ERROR;

    if(enIPStatus != Get_eGPRSState()){
        (void)GSM_GprsShutDown();
        (void)GSM_DetachToGPRS();
        if (enPDPdeactivated == Get_eGPRSState()){
            resp = GSM_GprsSingleConnectionMode();
            if(resp == GSM_OK){
                resp = GSM_AttachToGPRS();
                if(enIPInitial == Get_eGPRSState()){
                    (void)GSM_SetupAPN((uint8_t*)"moldcell");
                    if(enIPstart == Get_eGPRSState()){
                        (void)GSM_StartGPRS();
                        if(enIPGprsAct == Get_eGPRSState()){
                            (void) GSM_GetLocalIP();
                            if(enIPStatus == Get_eGPRSState()){
                                (void)GSM_StartServerConnection(ip_addr, port);
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        (void)GSM_StartServerConnection(ip_addr, port);
    }
}

GsmHttp_Response GSM_HttpPost(uint8_t* urlPath, uint8_t* postData){
    GsmHttp_Response tRsp = GSM_HTTP_RESPONSE_SERVER_ERROR;
    uint8_t responses;
    size_t postDataLen = strlen((const char*)postData);

    if (enIPStatus == Get_eGPRSState() || enIPprocessing == Get_eGPRSState())
    {
        responses = GSM_InitHTTP();
        if( GSM_OK == responses )
        {
            responses = GSM_SetHttpParameters(GSM_HTTP_PARAM_CID, (uint8_t*)"1");
            if( GSM_OK == responses )
            {
                responses = GSM_SetHttpParameters(GSM_HTTP_PARAM_URL, urlPath);
                if( GSM_OK == responses )
                {
                    responses = GSM_SetHTTPDataToTransfer(postData, postDataLen, 10000);
                    if (GSM_OK == responses)
                    {
                        tRsp = GSM_HttpMethodAction(GSM_HTTP_METHOD_POST);
                        GSM_HTTPTerminateService();
                    }
                }
            }
        }
    }
    return tRsp;
}

GsmHttp_Response GSM_HttpGet(uint8_t* urlPath){
    GsmHttp_Response tRsp = GSM_HTTP_RESPONSE_SERVER_ERROR;
    uint8_t responses;

    if (enIPStatus == Get_eGPRSState() || enIPprocessing == Get_eGPRSState())
    {
        responses = GSM_InitHTTP();
        if( GSM_OK == responses )
        {
            responses = GSM_SetHttpParameters(GSM_HTTP_PARAM_CID, (uint8_t*)"1");
            if( GSM_OK == responses )
            {
                responses = GSM_SetHttpParameters(GSM_HTTP_PARAM_URL, urlPath);
                if( GSM_OK == responses )
                {
                    tRsp = GSM_HttpMethodAction(GSM_HTTP_METHOD_GET);
                    GSM_HTTPTerminateService();
                }
            }
        }
    }
    return tRsp;
}

void GSM_ActivateGprs(void){
    uint8_t resp = GSM_ERROR;
    uint8_t tries = 0;

    while (enIPStatus != Get_eGPRSState())
    {
        if (tries == MAX_TRIES){
            Set_eGprsState(enPDPdeactivated);
            if (resp == GSM_TIMEOUT){
                Set_eGsmState(enUnreachable);
            }
            break;
        }

        if(enIPInitial != Get_eGPRSState()){
            GSM_GprsShutDown();
            if (enPDPdeactivated == Get_eGPRSState())
            {
                resp = GSM_GprsSingleConnectionMode();
                if(resp == GSM_OK)
                {
                    resp = GSM_SetBearerParameters((uint8_t*)"Contype", (uint8_t*)"GPRS");
                    if(resp == GSM_OK)
                    {
                        resp = GSM_SetBearerParameters((uint8_t*)"APN", (uint8_t*)"moldcell");
                        if (resp == GSM_OK)
                        {
                            resp = GSM_AttachToGPRS();
                            if (enIPInitial == Get_eGPRSState())
                            {
                                resp = GSM_OpenBearer();
                            }
                            else{
                                if(resp == GSM_ERROR){
                                    resp = GSM_DetachToGPRS();
                                    if(resp == GSM_OK){
                                        gsmDelay_ms(3000);
                                        resp = GSM_AttachToGPRS();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            resp = GSM_OpenBearer();
        }

        if (resp != GSM_OK){
            tries++;
        }
    }
}

uint8_t GSM_StartServerConnection(uint8_t* host, uint8_t* port){
    uint8_t resp = GSM_ERROR;
    uint8_t tries = 0;


    if(enIPStatus == Get_eGPRSState())
    {
        while ( enConnectOk != Get_eGPRSState() )
        {
            if (tries == MAX_TRIES){
                Set_eGprsState(enPDPdeactivated);
                if (resp == GSM_TIMEOUT){
                    Set_eGsmState(enUnreachable);
                }
                break;
            }
            (void)GSM_TcpSendMode(0);
            resp = GSM_ConnectToServer(host, port);

            if (resp != GSM_OK){
                tries++;
            }
        }
    }
    return resp;
}


void GSM_StopGprsConnection(void){
    if(enConnectOk == Get_eGPRSState())
    {
    	Set_eGprsState(enTcpClosing);
        GSM_GprsShutDown();
    }

}

