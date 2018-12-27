/*
 * GSM.h
 *
 *  Created on: 30 апр. 2017 г.
 *      Author: Dumitru
 */

#ifndef GSM_H_
#define GSM_H_


/*
 *
 *
 * **************************Imports************************************************
 *
 *
 * */

#include <stdlib.h>
#include <stdint.h>
#include "GSM_cnf.h"

/*
 *
 *
 * ***************************Public Macro Definitions*******************************
 *
 *
 * */

#define HTTP_METHOD_TIMEOUT                            (uint16_t)12000

#define MAX_TRIES                                      3

#define DEFAULT_PIN_CODE                               1111

/*
 *     -------------     Command responses definition      --------------------
 * */

#define GSM_OK                                         0x00
#define GSM_ERROR                                      0x01
#define GSM_TIMEOUT                                    0x02
#define GSM_ENTER_PIN                                  0x03
#define GSM_INSERT_SIM                                 0x04
#define GSM_GENERAL_ERROR                              0x05

#define GSM_NO_STATE_CHANGES                           0x00
#define GSM_GSM_STATE_CHANGES                          0x01
#define GSM_GPRS_STATE_CHANGES                         0x02

#define GSM_CALL_OK                                    0x10
#define GSM_CALL_NO_DIALTONE                           0x11
#define GSM_CALL_BUSY                                  0x12
#define GSM_CALL_NO_CARRIER                            0x13
#define GSM_CALL_NO_ANSWER                             0x14
#define GSM_CALL_ERROR_INCORRECT_NUMBER                0x15
#define GSM_CALL_ERROR                                 0x16


#define GSM_HTTP_RESPONSE_INFO                         0x31       /* 1XX response group  */
#define GSM_HTTP_RESPONSE_SUCCESS                      0x32       /* 2XX response group  */
#define GSM_HTTP_RESPONSE_REDIRECTION                  0x33       /* 3XX response group  */
#define GSM_HTTP_RESPONSE_CLIENT_ERROR                 0x34       /* 4XX response group  */
#define GSM_HTTP_RESPONSE_SERVER_ERROR                 0x35       /* 5XX response group  */


#define GSM_NO_RESPONSE_SAVE_NEEDED                    0x00
#define GSM_RESPONSE_SAVE_NEEDED                       0x01

#define GSM_HTTP_METHOD_GET                            0x00
#define GSM_HTTP_METHOD_POST                           0x01
#define GSM_HTTP_METHOD_HEAD                           0x02

/*
 *          -------------  HTTP Response codes  -------------
 * */

#define GSM_HTTP_RESPONSE_CONTINUE                     (GsmHttp_Response)0x64        /* 100 */
#define GSM_HTTP_RESPONSE_SWITCHING_PROTOCOL           (GsmHttp_Response)0x65        /* 101 */
#define GSM_HTTP_RESPONSE_OK                           (GsmHttp_Response)0xC8        /* 200 */
#define GSM_HTTP_RESPONSE_CREATED                      (GsmHttp_Response)0xC9        /* 201 */
#define GSM_HTTP_RESPONSE_ACCEPTED                     (GsmHttp_Response)0xCA        /* 202 */
#define GSM_HTTP_RESPONSE_NON_AUTH_INFO                (GsmHttp_Response)0xCB        /* 203 */
#define GSM_HTTP_RESPONSE_NO_CONTENT                   (GsmHttp_Response)0xCC        /* 204 */
#define GSM_HTTP_RESPONSE_RESET_CONTENT                (GsmHttp_Response)0xCD        /* 205 */
#define GSM_HTTP_RESPONSE_PARTIAL_CONTENT              (GsmHttp_Response)0xCE        /* 206 */
#define GSM_HTTP_RESPONSE_MILTIPLE_CHOICES             (GsmHttp_Response)0x12C       /* 300 */
#define GSM_HTTP_RESPONSE_MOVED_PERMANENTLY            (GsmHttp_Response)0x12D       /* 301 */
#define GSM_HTTP_RESPONSE_FOUND                        (GsmHttp_Response)0x12E       /* 302 */
#define GSM_HTTP_RESPONSE_SEE_OTHER                    (GsmHttp_Response)0x12F       /* 303 */
#define GSM_HTTP_RESPONSE_NOT_MODIFIED                 (GsmHttp_Response)0x130       /* 304 */
#define GSM_HTTP_RESPONSE_USE_PROXY                    (GsmHttp_Response)0x131       /* 305 */
#define GSM_HTTP_RESPONSE_TEMPORARY_REDIRECT           (GsmHttp_Response)0x133       /* 307 */
#define GSM_HTTP_RESPONSE_BAD_REQUEST                  (GsmHttp_Response)0x190       /* 400 */
#define GSM_HTTP_RESPONSE_UNAUTHORIZED                 (GsmHttp_Response)0x191       /* 401 */
#define GSM_HTTP_RESPONSE_PAYMENT_REQUIRED             (GsmHttp_Response)0x192       /* 402 */
#define GSM_HTTP_RESPONSE_FORBIDDEN                    (GsmHttp_Response)0x193       /* 403 */
#define GSM_HTTP_RESPONSE_NOT_FOUND                    (GsmHttp_Response)0x194       /* 404 */
#define GSM_HTTP_RESPONSE_METHOD_NOT_ALLOWED           (GsmHttp_Response)0x195       /* 405 */
#define GSM_HTTP_RESPONSE_NOT_ACCEPTABLE               (GsmHttp_Response)0x196       /* 406 */
#define GSM_HTTP_RESPONSE_PROXY_AUTH_REQIURED          (GsmHttp_Response)0x197       /* 407 */
#define GSM_HTTP_RESPONSE_REQUEST_TIMEOUT              (GsmHttp_Response)0x198       /* 408 */
#define GSM_HTTP_RESPONSE_CONFLICT                     (GsmHttp_Response)0x199       /* 409 */
#define GSM_HTTP_RESPONSE_INTERNAL_SERVER_ERROR        (GsmHttp_Response)0x1F4       /* 500 */
#define GSM_HTTP_RESPONSE_NOT_IMPLEMENTED              (GsmHttp_Response)0x1F5       /* 501 */
#define GSM_HTTP_RESPONSE_BAD_GATEWAY                  (GsmHttp_Response)0x1F6       /* 502 */
#define GSM_HTTP_RESPONSE_SERVICE_UNAVAILABLE          (GsmHttp_Response)0x1F7       /* 503 */
#define GSM_HTTP_RESPONSE_GATEWAY_TIMEOUT              (GsmHttp_Response)0x1F8       /* 504 */
#define GSM_HTTP_RESPONSE_HTTP_VERSION_NOT_SUPPORTED   (GsmHttp_Response)0x1F9       /* 505 */
#define GSM_HTTP_RESPONSE_NOT_HTTP_DPU                 (GsmHttp_Response)0x258       /* 600 */
#define GSM_HTTP_RESPONSE_NETWORK_ERROR                (GsmHttp_Response)0x259       /* 601 */
#define GSM_HTTP_RESPONSE_NO_MEMORY                    (GsmHttp_Response)0x25A       /* 602 */
#define GSM_HTTP_RESPONSE_DNS_ERROR                    (GsmHttp_Response)0x25B       /* 603 */
#define GSM_HTTP_RESPONSE_STACK_BUSY                   (GsmHttp_Response)0x25C       /* 604 */




/***************************Public Type Definitions********************************/


typedef enum{
    enIDLE = 0,
    enRDY = 1,
    enCallReady = 2,
    enOK = 3,
    enReset = 4,
    enCalling = 6,
    enNoSIM = 7,
    enUnreachable = 8,

}GSM_STATE;

typedef enum{
    enIPInitial = 0,
    enIPstart,
    enIPConfig,
    enIPGprsAct,
    enIPStatus,
    enIPprocessing,
	enTcpConnecting,
	enConnectOk,
	enTcpClosing,
	enTcpClosed,
    enPDPdeactivated,

}GSM_GPRS_STATE;


typedef enum
{
	enCommIdle = 0,
	enCommBusy
}GSM_COMM_STATE;


typedef uint16_t GsmHttp_Response;

/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

uint8_t CheckGsmPersistance(void);
uint8_t GSM_SetBaudRate(uint16_t baud);
uint8_t GSM_PowerDown(void);
uint8_t GSM_EnterPinCode(uint16_t pinCode);
uint8_t GSM_CallNumber(uint8_t* str);
uint8_t GSM_AttachToGPRS(void);
uint8_t GSM_DetachToGPRS(void);
uint8_t GSM_SetupAPN(uint8_t* apn);
uint8_t GSM_GprsSingleConnectionMode(void);
uint8_t GSM_StartGPRS(void);
uint8_t GSM_GetLocalIP(void);
uint8_t GSM_GprsShutDown(void);
uint8_t GSM_ConnectToServer(uint8_t* host, uint8_t* port);
uint8_t GSM_InitHTTP(void);
uint8_t GSM_SetHttpParameters(uint8_t HTTPParamTag, uint8_t* HTTPParmValue);
uint8_t GSM_SetHTTPDataToTransfer(uint8_t* postData, uint16_t nrOfBytes, uint16_t latencyTime);
uint8_t GSM_SetBearerParameters( uint8_t* ConParamTag, uint8_t* ConParamValue);
uint8_t GSM_OpenBearer(void);
uint8_t GSM_HttpMethodAction(uint8_t method);
uint8_t GSM_HTTPTerminateService(void);
uint8_t GSM_ReceiveCallResponse(void);
uint8_t GSM_StartServerConnection(uint8_t* host, uint8_t* port);
GSM_GPRS_STATE GSM_GetSimGprsState(void);


void GSM_StopGprsConnection(void);
void GSM_Init(void);
void GSM_RejectCall(void);
void GSM_ServerSocketConnection(uint8_t* ip_addr, uint8_t* port);
void GSM_ActivateGprs(void);


GSM_STATE      Get_eGsmState(void);
GSM_GPRS_STATE Get_eGPRSState(void);
GSM_COMM_STATE Get_eGsmCommState(void);

GsmHttp_Response GSM_HttpPost(uint8_t* urlPath, uint8_t* postData);
GsmHttp_Response GSM_HttpGet(uint8_t* urlPath);

#endif /* GSM_GSM_H_ */
