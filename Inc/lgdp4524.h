/*
 * lgdp4524.h
 *
 *  Created on: 12 џэт. 2018 у.
 *      Author: Dumitru
 */

#ifndef LGDP4524_H_
#define LGDP4524_H_


/***************************Imports*************************************************/

#include <stdint.h>
#include "lgdp4524if.h"
#include "lgdp4524_cmd.h"

/***************************Public Macro Definitions********************************/

#define bitmapdatatype           uint8_t*

#define LEFT   0
#define RIGHT  9999
#define CENTER 9998

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/***************************Public Type Definitions********************************/

typedef uint8_t boolean;

typedef struct
{
    uint8_t* font;
    uint8_t x_size;
    uint8_t y_size;
    uint8_t offset;
    uint8_t numchars;
}CurrentFontType;


typedef enum{
    enLandscape = 0,
    enPortrait
}DisplayOrientationType;

typedef union{
    uint16_t instructionReg;
    struct{
        uint8_t SR;

        union{
            uint8_t value;
            struct{
                unsigned IB_7:1;
                unsigned IB_6:1;
                unsigned IB_5:1;
                unsigned IB_4:1;
                unsigned IB_3:1;
                unsigned IB_2:1;
                unsigned IB_1:1;
                unsigned IB_0:1;
            }Bit;
        }IR;
    }instruction;
}InstructionType;

typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t z;
}TSPoint;

/***************************Public Data Definitions********************************/

extern DisplayOrientationType displayOrientation;

/***************************Public Function Definitions****************************/

void     LCD_LGDP4524_Init(DisplayOrientationType orientation);
void     SetBrushColor(uint8_t r, uint8_t g, uint8_t b);
void     FillScr(uint8_t r, uint8_t g, uint8_t b);
uint16_t GetBrushColor(void);
void     SetBackColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alfa);
uint16_t GetBackColor(void);
void     SetPixel(uint16_t color);
void     DrawRect(int16_t x, int16_t y, int16_t w, int16_t h);
void     FillRect(int16_t x, int16_t y, int16_t w, int16_t h);
void     FillRoundRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void     FillCircle(int16_t x, int16_t y, int16_t radius, uint16_t c);
void     ClrScr(void);
void     Print(uint8_t *st, int16_t x, int16_t y, int16_t deg);
void     DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void     DrawPixel(int16_t x, int16_t y);
void     SetFont(uint8_t* cfont);
void     DrawBitmap(int16_t x, int16_t y, int16_t sx, int16_t sy, bitmapdatatype data, int16_t scale);
void     PrintNumI(int32_t num, int16_t x, int16_t y, int16_t length, uint8_t filler);

void LCD_Write_Com_Data(uint16_t com1, uint16_t data);

#endif /* LGDP4524_H_ */
