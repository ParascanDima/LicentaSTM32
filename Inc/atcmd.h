/*
 * atcmd.h
 *
 *  Created on: 11 окт. 2017 г.
 *      Author: Dumitru
 */

#ifndef ATCMD_H_
#define ATCMD_H_


/***************************Imports*************************************************/

#include <stdint.h>

/***************************Public Macro Definitions********************************/

#define GSM_HTTP_PARAM_CID                             0x01
#define GSM_HTTP_PARAM_URL                             0x02
#define GSM_HTTP_PARAM_UA                              0x03
#define GSM_HTTP_PARAM_PROIP                           0x04
#define GSM_HTTP_PARAM_PROPORT                         0x05
#define GSM_HTTP_PARAM_REDIR                           0x06
#define GSM_HTTP_PARAM_BREAK                           0x07
#define GSM_HTTP_PARAM_BREAKEND                        0x08
#define GSM_HTTP_PARAM_TIMEOUT                         0x09
#define GSM_HTTP_PARAM_CONTENT                         0x0A

/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/
void gsmAT_CPOWD           (void);

void gsmAT_CGATT           (uint8_t param);

void gsmAT_CSTT            (uint8_t* apn);

void gsmAT_CIICR           (void);

void gsmAT_CIFSR           (void);

void gsmAT_CIPMUX          (uint8_t conType);

void gsmAT_CIPSTART        (uint8_t* host, uint8_t* port);

void gsmAT_CIPSHUT         (void);

void gsmAT_HTTPINIT        (void);

void gsmAT_HTTPPARA        (uint8_t HTTPParamTag, uint8_t* HTTPParmValue);

void gsmAT_HTTPDATA        (uint16_t nrOfBytes, uint16_t latencyTime);

void gsmAT_HTTPACTION      (uint8_t method);

void gsmAT_HTTPTERM        (void);

void gsmATH0               (void);

void gsmATD                (uint8_t* phoneNumber);

void gsmAT_SAPBR      (uint8_t cmd_type, uint8_t cid, uint8_t* ConParamTag, uint8_t* ConParamValue);

void gsmAT_IPR             (uint16_t baud);

void gsmCheckNetworkRegistration(void);

void gsmCheckGprsConnection(void);

void gsmAT_CPIN            (uint16_t pinCode);


#endif /* ATCMD_H_ */
