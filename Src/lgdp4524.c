/*
 * lgdp4524.c
 *
 *  Created on: 12 џэт. 2018 у.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "lgdp4524.h"
#include "lgdp4524if.h"
#include "lgdp4524_pinout.h"
#include "lgdp4524_cmd.h"
#include <math.h>
#include <string.h>

/**************Private Macro Definitions*****************/

#define u8_to_u16(a, b) ((uint16_t)((uint16_t)((uint16_t)a<<8)|(uint16_t)b))
#define pgm_read_byte(addr)      (*(const uint8_t *)(addr))
#define pgm_read_word(addr)      (*(const uint16_t *)(addr))
#define fontbyte(x)              pgm_read_byte(&font.font[x])
#define rgb(color)               (uint8_t)((uint16_t)color>>11), (uint8_t)(((uint16_t)color>>5)&0x3F), (uint8_t)((uint16_t)color&0x1F)          // rrrrrggggggbbbbb
#define NUMSAMPLES               2
/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/

const uint8_t display_size_x = 175;
const uint8_t display_size_y = 219;
DisplayOrientationType displayOrientation;
CurrentFontType font;

uint8_t brushColorH, brushColorL, backColorH, backColorL;
uint8_t transparent;


/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/


uint16_t read_control_register(void){

    uint16_t reg_val = 0;
#ifndef FSMC_IS_USED
    /*
     * The BUS direction should be changed for read data through BUS
     */
    SetDataDirectionRegister(LCD_INPUT_BUS);

    /*
     * RD pin should be low to read
     */
    PullDownRD();
    PullDownCS();
    reg_val = ((uint16_t)GetDataFromParallelPort()<<8);
    /*
     * to indicate the end of read  of first byte the RD pin should be pulsed
     */
    PULSE_HIGH(RD);
    reg_val |= (uint16_t)GetDataFromParallelPort();
    /*
     * Reset value of controll pins to HIGH
     */
    PullUpRD();
    PullUpCS();

    /*
     * Reset the direction of BUS to OUTPUT
     */
    SetDataDirectionRegister(LCD_OUTPUT_BUS);
#else
    reg_val = FSMC_Read_Data();
#endif

    return reg_val;

}


void write_control_register(uint16_t data)
{
#ifndef FSMC_IS_USED
    SetDataToParallelPort((uint8_t)(data>>8));
    PullDownWR();
    PULSE_LOW(CS);
    PullUpWR();
    SetDataToParallelPort((uint8_t)(data&0x00FF));
    PullDownWR();
    PULSE_LOW(CS);
    PullUpWR();
#else
    FSMC_Write_Data(data);
#endif
}

/*
 * For writing index to IR the next configuration should be set:
 * WR = 0, RD = 1, RS = 0.
 * RD, RS and WR by default are set to 1, the 0 should be set on WR and RS.
 */
void set_index_register(uint16_t index_R){
#ifndef FSMC_IS_USED
    PullDownWR();
    PullDownRS();
    PULSE_LOW(CS);  //transfer first byte ; value = doesnt matter
    PullUpWR();
    SetDataToParallelPort((uint8_t)index_R);
    PullDownWR();
    PULSE_LOW(CS);
    PullUpRS();
    PullUpWR();

#else
    FSMC_Write_Cmd(index_R);
#endif
}


/**************Public Function Definitions***************/


void LCD_Write_Com(uint8_t com)
{
    set_index_register(com);
}

void LCD_Write_Data8(uint8_t data)
{
    write_control_register((uint16_t)data);
}

void LCD_Write_Data16(uint16_t data)
{
    write_control_register(data);
}


void LCD_Write_Com_Data(uint16_t com1, uint16_t data)
{
    set_index_register(com1);
    write_control_register(data);
}



void LCD_LGDP4524_Init(DisplayOrientationType orientation)
{
    LGDP4524_PinoutInit();
    PullUpRST();
    displayOrientation = orientation;
    LGDP4524_Delay_ms(10);
    PullDownRST();
    LGDP4524_Delay_ms(10);
    PullUpRST();

    LGDP4524_Delay_ms(150);
    LCD_Write_Com_Data(DisplayCtrl_1,0x0000);                                     // R07h = 0x0000
    LCD_Write_Com_Data(PwrCtrl_3,0x0000);                                         // R12h = 0x0000
    LCD_Write_Com_Data(PwrCtrl_4,0x0000);                                         // R13h = 0x0000
    LCD_Write_Com_Data(PwrCtrl_5,RI_1|RI_0|RV_1|RV_0);                            // R14h = 0x0330
    LGDP4524_Delay_ms(150);

    LCD_Write_Com_Data(PwrCtrl_2, DC1_0|VC_0);                                    // R11h = 0x0101
    LCD_Write_Com_Data(PwrCtrl_3, VRH_3|VRH_1);                                   // R12h = 0x000A
    LCD_Write_Com_Data(PwrCtrl_4, VDV_3|VDV_2|VDV_0|VCM_6|VCM_2|VCM_0);           // R13h = 0x0D45
    LCD_Write_Com_Data(PwrCtrl_1, BT_0|AP_2|AP_1|DK);                             // R10h = 0x0164
    LCD_Write_Com_Data(PwrCtrl_3, PON|VRH_3|VRH_1);                               // R12h = 0x001A
    LGDP4524_Delay_ms(150);
    LCD_Write_Com_Data(PwrCtrl_4, VCOMG|VDV_3|VDV_2|VDV_0|VCM_6|VCM_2|VCM_0);     // R13h = 0x2D45
    LCD_Write_Com_Data(PwrCtrl_1, BT_0|AP_2|AP_1);                                // R10h = 0x0160
    LGDP4524_Delay_ms(150);
    LCD_Write_Com_Data(EpromCtrl_1, POR);                                         // R60h = 0x2000
    LCD_Write_Com_Data(EpromCtrl_1, 0x0000);                                      // R60h = 0x0000
    LCD_Write_Com_Data(EpromCtrl_2, VCMSEL_1);                                    // R61h = 0x0002
    LGDP4524_Delay_ms(50);
    LCD_Write_Com_Data(DrvOutputCtrl, SS|NL_4|NL_3|NL_1|NL_0);                    // R01h = 0x011B
    LCD_Write_Com_Data(DrivingWaveformCtrl, FLD_0|B_C|EOR);                       // R02h = 0x0700
    LCD_Write_Com_Data(EntryMode, BGR|ID__1|ID__0);                               // R03h = 0x1030
    LCD_Write_Com_Data(DisplayCtrl_2, FP_2|FP_0|BP_2);                            // R08h = 0x0504
    LCD_Write_Com_Data(DisplayCtrl_3, 0x0000);                                    // R09h = 0x0000
    LCD_Write_Com_Data(FrameCycleCtrl, EQ_1|EQ_0|RTN_5|RTN_4);                    // R0Bh = 0x0C30
    LCD_Write_Com_Data(RamAddrSet, 0x0000);                                       // R21h = 0x0000
    LCD_Write_Com_Data(yControl_0, PKP1_2|PKP1_1|PKP0_2|PKP0_1);                  // R30h = 0x0606
    LCD_Write_Com_Data(yControl_1, PKP3_2|PKP3_1|PKP2_2|PKP2_1);                  // R31h = 0x0606
    LCD_Write_Com_Data(yControl_2, PKP5_2|PKP5_1|PKP4_2|PKP4_1);                  // R32h = 0x0606
    LCD_Write_Com_Data(yControl_3, PRP0_1|PRP0_0);                                // R33h = 0x0003
    LCD_Write_Com_Data(yControl_4, PKN1_1|PKN0_1);                                // R34h = 0x0202
    LCD_Write_Com_Data(yControl_5, PKN3_2|PKN2_2);                                // R35h = 0x0404
    LCD_Write_Com_Data(yControl_6, PKN5_2|PKN4_2);                                // R36h = 0x0404
    LCD_Write_Com_Data(yControl_7, PRN1_2|PRN0_2);                                // R37h = 0x0404
    LCD_Write_Com_Data(yControl_8, VRP1_2|VRP0_1);                                // R38h = 0x0402
    LCD_Write_Com_Data(yControl_9, VRN1_4|VRN0_3|VRN0_2);                         // R39h = 0x100C
    LCD_Write_Com_Data(yControl_A, PFP1_0|PFP0_0);                                // R3Ah = 0x0101
    LCD_Write_Com_Data(yControl_B, PFP3_0|PFP2_0);                                // R3Bh = 0x0101
    LCD_Write_Com_Data(yControl_C, PFN1_0|PFN0_0);                                // R3Ch = 0x0101
    LCD_Write_Com_Data(yControl_D, PFN3_0|PFN2_0);                                // R3Dh = 0x0101
    LCD_Write_Com_Data(yControl_E, PMP_0);                                        // R3Eh = 0x0001
    LCD_Write_Com_Data(yControl_F, PMN_0);                                        // R3Fh = 0x0001
    LCD_Write_Com_Data(FirstScreenDrivePos, SE1_7|SE1_6|SE1_4|SE1_3|SE1_1|SE1_0); // R42h = 0xDB00
    LCD_Write_Com_Data(HorizontalRamAddrPos, HEA_7|HEA_5|HEA_3|HEA_2|HEA_1|HEA_0); // R44h = 0xAF00
    LCD_Write_Com_Data(VerticalRamAddrPos, VEA_7|VEA_6|VEA_4|VEA_3|VEA_1|VEA_0);  // R45h = 0xDB00
    LGDP4524_Delay_ms(50);
    LCD_Write_Com_Data(TestReg_1, T8CL);                                          // R71h = 0x0040
    LCD_Write_Com_Data(TestReg_2, MVCI);                                          // R72h = 0x0002
    LGDP4524_Delay_ms(50);
    LCD_Write_Com_Data(PwrCtrl_1, SAP_2|SAP_1|AP_2|AP_1);                         // R10h = 0x6060
    LCD_Write_Com_Data(DisplayCtrl_1, REV|D_0);                                   // R07h = 0x0005
    LGDP4524_Delay_ms(50);
    LCD_Write_Com_Data(DisplayCtrl_1, GON|REV|D_0);                               // R07h = 0x0025
    LCD_Write_Com_Data(DisplayCtrl_1, GON|REV|D_1|D_0);                           // R07h = 0x0027
    LGDP4524_Delay_ms(50);
    LCD_Write_Com_Data(DisplayCtrl_1, GON|DTE|REV|D_1|D_0);                       // R07h = 0x0037
    LCD_Write_Com_Data(RamAddrSet, 0x0000);                                       // R21h = 0x0000

    LCD_Write_Com(GramWriteData);

    SetBrushColor(255, 255, 255);
    SetBackColor(0, 0, 0, 0);

}

#ifndef FSMC_IS_USED
void _fast_fill_8(uint8_t ch, uint32_t pix)
{
    uint32_t blocks;
    uint16_t i;

    SetDataToParallelPort(ch);
    blocks = pix/16;
    PullDownCS();
    for (i=0; i<blocks; i++)
    {
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
        PULSE_LOW(WR);PULSE_LOW(WR);
	  }
	  if ((pix % 16) != 0)
		for (i=0; i<(pix % 16)+1; i++)
		{
           PULSE_LOW(WR);PULSE_LOW(WR);
        }
    PullUpCS();

}
#endif


void SetXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (displayOrientation==enLandscape)
    {
        SWAP(uint16_t, x1, y1);
        SWAP(uint16_t, x2, y2)
        y1=display_size_y-y1;
        y2=display_size_y-y2;
        SWAP(uint16_t, y1, y2)
    }

    LCD_Write_Com_Data(HorizontalRamAddrPos, (x2<<8)+x1);
    LCD_Write_Com_Data(VerticalRamAddrPos, (y2<<8)+y1);
    LCD_Write_Com_Data(RamAddrSet, (y1<<8)+x1);
    LCD_Write_Com(GramWriteData);

}

void ClrXY()
{
    if (displayOrientation==enPortrait)
        SetXY(0,0,display_size_x,display_size_y);
    else
        SetXY(0,0,display_size_y,display_size_x);
}

void SetPixel(uint16_t color)
{
	LCD_Write_Com_Data(GramWriteData,color);    // rrrrrggggggbbbbb
}


void DrawPixel(int16_t x, int16_t y)
{

    SetXY(x, y, x, y);
    SetPixel(u8_to_u16(brushColorH, brushColorL));

    ClrXY();
}


void DrawHLine(int16_t x, int16_t y, int16_t l)
{
    int16_t i;

    if (l<0)
    {
        l = -l;
        x -= l;
    }

    SetXY(x, y, x+l, y);
#ifndef FSMC_IS_USED
    if (brushColorH==brushColorL)
    {
        _fast_fill_8(brushColorH,l);
    }
    else
    {
#endif
        for (i=0; i<l+1; i++)
        {
            LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        }
#ifndef FSMC_IS_USED
    }
#endif
    ClrXY();
}

void DrawVLine(int16_t x, int16_t y, int16_t l)
{
    int16_t i;

    if (l<0)
    {
        l = -l;
        y -= l;
    }

    SetXY(x, y, x, y+l);
#ifndef FSMC_IS_USED
    if (brushColorH==brushColorL)
    {
        _fast_fill_8(brushColorH,l);
    }
    else
    {
#endif
        for (i=0; i<l+1; i++)
        {
            LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        }
#ifndef FSMC_IS_USED
    }
#endif
    ClrXY();
}


void DrawRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    if (x1>x2)
    {
        SWAP(int16_t, x1, x2);
    }
    if (y1>y2)
    {
        SWAP(int16_t, y1, y2);
    }

    DrawHLine(x1, y1, x2-x1);
    DrawHLine(x1, y2, x2-x1);
    DrawVLine(x1, y1, y2-y1);
    DrawVLine(x2, y1, y2-y1);
}


void DrawColoredRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c)
{
  SetBrushColor(rgb(c));
  DrawRect(x, y,x+w-1 , y+h-1);
}


void DrawRoundRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    if (x1>x2)
    {
        SWAP(int16_t, x1, x2);
    }
    if (y1>y2)
    {
        SWAP(int16_t, y1, y2);
    }
    if ((x2-x1)>4 && (y2-y1)>4)
    {
        DrawPixel(x1+1,y1+1);
        DrawPixel(x2-1,y1+1);
        DrawPixel(x1+1,y2-1);
        DrawPixel(x2-1,y2-1);
        DrawHLine(x1+2, y1, x2-x1-4);
        DrawHLine(x1+2, y2, x2-x1-4);
        DrawVLine(x1, y1+2, y2-y1-4);
        DrawVLine(x2, y1+2, y2-y1-4);
    }
}


void FillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int16_t i;

    if (x1>x2)
    {
        SWAP(int16_t, x1, x2);
    }
    if (y1>y2)
    {
        SWAP(int16_t, y1, y2);
    }
#ifndef FSMC_IS_USED
    if (brushColorH==brushColorL)
    {

        SetXY(x1, y1, x2, y2);
        _fast_fill_8(brushColorH,(((int32_t)(x2-x1)+1)*((int32_t)(y2-y1)+1)));

    }
    else
    {
#endif
        if (displayOrientation==enPortrait)
        {
            for (i=0; i<((y2-y1)/2)+1; i++)
            {
                DrawHLine(x1, y1+i, x2-x1);
                DrawHLine(x1, y2-i, x2-x1);
            }
        }
        else
        {
            for (i=0; i<((x2-x1)/2)+1; i++)
            {
                DrawVLine(x1+i, y1, y2-y1);
                DrawVLine(x2-i, y1, y2-y1);
            }
        }
#ifndef FSMC_IS_USED
    }
#endif
}


void FillColoredRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c)
{
  SetBrushColor(rgb(c));
  FillRect(x, y, x+w-1, y+h-1);
}


void FillRoundRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int16_t i;

    if (x1>x2)
    {
        SWAP(int16_t, x1, x2);
    }
    if (y1>y2)
    {
        SWAP(int16_t, y1, y2);
    }

    if ((x2-x1)>4 && (y2-y1)>4)
    {
        for (i=0; i<((y2-y1)/2)+1; i++)
        {
            switch(i)
            {
            case 0:
                DrawHLine(x1+2, y1+i, x2-x1-4);
                DrawHLine(x1+2, y2-i, x2-x1-4);
                break;
            case 1:
                DrawHLine(x1+1, y1+i, x2-x1-2);
                DrawHLine(x1+1, y2-i, x2-x1-2);
                break;
            default:
                DrawHLine(x1, y1+i, x2-x1);
                DrawHLine(x1, y2-i, x2-x1);
            }
        }
    }
}

void DrawCircle(int16_t x, int16_t y, int16_t radius)
{
    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x1 = 0;
    int16_t y1 = radius;


    SetXY(x, y + radius, x, y + radius);
    LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
    SetXY(x, y - radius, x, y - radius);
    LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
    SetXY(x + radius, y, x + radius, y);
    LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
    SetXY(x - radius, y, x - radius, y);
    LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));

    while(x1 < y1)
    {
        if(f >= 0)
        {
            y1--;
            ddF_y += 2;
            f += ddF_y;
        }
        x1++;
        ddF_x += 2;
        f += ddF_x;
        SetXY(x + x1, y + y1, x + x1, y + y1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x - x1, y + y1, x - x1, y + y1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x + x1, y - y1, x + x1, y - y1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x - x1, y - y1, x - x1, y - y1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x + y1, y + x1, x + y1, y + x1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x - y1, y + x1, x - y1, y + x1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x + y1, y - x1, x + y1, y - x1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
        SetXY(x - y1, y - x1, x - y1, y - x1);
        LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
    }

    ClrXY();
}

void __FillCircle__(int16_t x, int16_t y, int16_t radius)
{
    int16_t y1, x1;

    for(y1=-radius; y1<=0; y1++)
        for(x1=-radius; x1<=0; x1++)
            if(x1*x1+y1*y1 <= radius*radius)
            {
                DrawHLine(x+x1, y+y1, 2*(-x1));
                DrawHLine(x+x1, y-y1, 2*(-x1));
                break;
            }
}

void FillCircle(int16_t x, int16_t y, int16_t radius, uint16_t c)
{
    __FillCircle__(x,y, radius);
}

void Show_color_bar()
{
    uint32_t i,j;

    ClrXY();
        for (i=0; i<(display_size_y+1); i++)
            {
                for (j=0; j<(display_size_x+1); j++)
                {
                      if(i>350){LCD_Write_Data8(0xFF);LCD_Write_Data8(0xFF);}
                      else if(i>300){LCD_Write_Data8(0x00);LCD_Write_Data8(0x1F);}
                      else if(i>250){LCD_Write_Data8(0x07);LCD_Write_Data8(0xE0);}
                      else if(i>200){LCD_Write_Data8(0x7F);LCD_Write_Data8(0xFF);}
                      else if(i>150){LCD_Write_Data8(0xF8);LCD_Write_Data8(0x00);}
                      else if(i>100){LCD_Write_Data8(0xF8);LCD_Write_Data8(0x1F);}
                      else if(i>50){LCD_Write_Data8(0xFF);LCD_Write_Data8(0xE0);}
                    else {LCD_Write_Data8(213);LCD_Write_Data8(156);}
                }
            }

}

void ClrScr()
{

    ClrXY();
#ifndef FSMC_IS_USED
    _fast_fill_8(0,(uint32_t)((uint16_t)(display_size_x+1)*(uint16_t)(display_size_y+1)));
#else
    FillScr(0, 0, 0);
#endif

}

void __FillScr__(uint16_t color)
{
    uint16_t i;
    uint8_t ch=0;
    uint8_t cl=0;

    ch=(uint8_t)(color>>8);
    cl=(uint8_t)color & 0xFF;


    ClrXY();
#ifndef FSMC_IS_USED
    if (ch==cl){
        _fast_fill_8(ch,(uint32_t)((uint16_t)(display_size_x+1)*(uint16_t)(display_size_y+1)));
    }
    else
    {
#endif
        for (i=0; i<(uint16_t)((uint16_t)(display_size_x+1)*(uint16_t)(display_size_y+1)); i++)
        {
            LCD_Write_Data16(u8_to_u16(ch,cl));
        }
#ifndef FSMC_IS_USED
    }
#endif
}

void FillScr(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
    __FillScr__(color);
}

void SetBrushColor(uint8_t r, uint8_t g, uint8_t b)
{
    brushColorH=((r&248)|g>>5);
    brushColorL=((g&28)<<3|b>>3);
}

uint16_t GetBrushColor(void)
{
    return (uint16_t)((brushColorH<<8) | brushColorL);
}

void SetBackColor(uint8_t r, uint8_t g, uint8_t b, uint8_t alfa)
{
    backColorH=((r&248)|g>>5);
    backColorL=((g&28)<<3|b>>3);
    transparent=alfa;
}

uint16_t GetBackColor(void)
{
    return (uint16_t)((backColorH<<8) | backColorL);
}


void DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    uint16_t    dx;
    int16_t  xstep;
    uint16_t    dy;
    int16_t  ystep;
    int16_t    col;
    uint16_t   row;
    int16_t t;

    if (y1==y2)
        DrawHLine(x1, y1, x2-x1);
    else if (x1==x2)
        DrawVLine(x1, y1, y2-y1);
    else
    {

        dx = (x2 > x1 ? x2 - x1 : x1 - x2);
        xstep =  x2 > x1 ? 1 : -1;
        dy = (y2 > y1 ? y2 - y1 : y1 - y2);
        ystep =  y2 > y1 ? 1 : -1;
        col = x1;
        row = y1;


        if (dx < dy)
        {
            t = - (dy >> 1);
            while (1)
            {
                SetXY (col, row, col, row);
                LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
                if (row == y2)
                    break;
                row += ystep;
                t += dx;
                if (t >= 0)
                {
                    col += xstep;
                    t   -= dy;
                }
            }
        }
        else
        {
            t = - (dx >> 1);
            while (1)
            {
                SetXY (col, row, col, row);
                LCD_Write_Data16(u8_to_u16(brushColorH, brushColorL));
                if (col == x2)
                    break;
                col += xstep;
                t += dy;
                if (t >= 0)
                {
                    row += ystep;
                    t   -= dx;
                }
            }
        }

    }
    ClrXY();
}


void PrintChar(int8_t c, int16_t x, int16_t y)
{
    int8_t i,ch;
    uint16_t j;
    uint16_t temp;
    int16_t zz;



    if (!transparent)
    {
        if (displayOrientation==enPortrait)
        {
            SetXY(x,y,x+font.x_size-1,y+font.y_size-1);

            temp=((c-font.offset)*((font.x_size/8)*font.y_size))+4;
            for(j=0;j<((font.x_size/8)*font.y_size);j++)
            {
                ch=pgm_read_byte(&font.font[temp]);
                for(i=0;i<8;i++)
                {
                    if((ch&(1<<(7-i)))!=0)
                    {
                        SetPixel((brushColorH<<8)|brushColorL);
                    }
                    else
                    {
                        SetPixel((backColorH<<8)|backColorL);
                    }
                }
                temp++;
            }
        }
        else
        {
            temp=((c-font.offset)*((font.x_size/8)*font.y_size))+4;

            for(j=0;j<((font.x_size/8)*font.y_size);j+=(font.x_size/8))
            {
                SetXY(x,y+(j/(font.x_size/8)),x+font.x_size-1,y+(j/(font.x_size/8)));
                for (zz=(font.x_size/8)-1; zz>=0; zz--)
                {
                    ch=pgm_read_byte(&font.font[temp+zz]);
                    for(i=0;i<8;i++)
                    {
                        if((ch&(1<<i))!=0)
                        {
                            SetPixel((brushColorH<<8)|brushColorL);
                        }
                        else
                        {
                            SetPixel((backColorH<<8)|backColorL);
                        }
                    }
                }
                temp+=(font.x_size/8);
            }
        }
    }
    else
    {
        temp=((c-font.offset)*((font.x_size/8)*font.y_size))+4;
        for(j=0;j<font.y_size;j++)
        {
            for (zz=0; zz<(font.x_size/8); zz++)
            {
                ch=pgm_read_byte(&font.font[temp+zz]);
                for(i=0;i<8;i++)
                {
                    SetXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);

                    if((ch&(1<<(7-i)))!=0)
                    {
                        SetPixel((brushColorH<<8)|brushColorL);
                    }
                }
            }
            temp+=(font.x_size/8);
        }
    }


    ClrXY();
}

/*
void RotateChar(int8_t c, int16_t x, int16_t y, int16_t pos, int16_t deg)
{
    int16_t zz;
    int8_t i,j,ch;
    uint16_t temp;
    int16_t newx,newy;
    double radian;
    radian=deg*0.0175;



    temp=((c-font.offset)*((font.x_size/8)*font.y_size))+4;
    for(j=0;j<font.y_size;j++)
    {
        for (zz=0; zz<(font.x_size/8); zz++)
        {
            ch=pgm_read_byte(&font.font[temp+zz]);
            for(i=0;i<8;i++)
            {
                newx=x+(((i+(zz*8)+(pos*font.x_size))*cos(radian))-((j)*sin(radian)));
                newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*font.x_size))*sin(radian)));

                SetXY(newx,newy,newx+1,newy+1);

                if((ch&(1<<(7-i)))!=0)
                {
                    setPixel((brushColorH<<8)|brushColorL);
                }
                else
                {
                    if (!transparent)
                        setPixel((backColorH<<8)|backColorL);
                }
            }
        }
        temp+=(font.x_size/8);
    }

    ClrXY();
}
*/

void Print(uint8_t *st, int16_t x, int16_t y, int16_t deg)
{
    int16_t stl, i;

    stl = strlen((const char*)st);

    if (displayOrientation==enPortrait)
    {
        if (x==RIGHT)
            x=(display_size_x+1)-(stl*font.x_size);
        if (x==CENTER)
            x=((display_size_x+1)-(stl*font.x_size))/2;
    }
    else
    {
        if (x==RIGHT)
            x=(display_size_y+1)-(stl*font.x_size);
        if (x==CENTER)
            x=((display_size_y+1)-(stl*font.x_size))/2;
    }

    for (i=0; i<stl; i++)
        if (deg==0)
            PrintChar(*st++, x + (i*(font.x_size)), y);
        //else
        //    RotateChar(*st++, x, y, i, deg);
}

void PrintNumI(int32_t num, int16_t x, int16_t y, int16_t length, uint8_t filler)
{
    uint8_t buf[25];
    uint8_t st[27];
    boolean neg=0;
    int16_t c=0, f=0;
    int16_t i;

    if (num==0)
    {
        if (length!=0)
        {
            for (c=0; c<(length-1); c++)
                st[c]=filler;
            st[c]=48;
            st[c+1]=0;
        }
        else
        {
            st[0]=48;
            st[1]=0;
        }
    }
    else
    {
        if (num<0)
        {
            neg=1;
            num=-num;
        }

        while (num>0)
        {
            buf[c]=48+(num % 10);
            c++;
            num=(num-(num % 10))/10;
        }
        buf[c]=0;

        if (neg)
        {
            st[0]=45;
        }

        if (length>(c+neg))
        {
            for (i=0; i<(length-c-neg); i++)
            {
                st[i+neg]=filler;
                f++;
            }
        }

        for (i=0; i<c; i++)
        {
            st[i+neg+f]=buf[c-i-1];
        }
        st[c+neg+f]=0;

    }

    Print(st,x,y,0);
}
/*
void PrintNumF(double num, int8_t dec, int16_t x, int16_t y, uint8_t divider, int16_t length, uint8_t filler)
{
    int16_t i;
    uint8_t st[27];
    boolean neg=0;

    if (dec<1)
        dec=1;
    else if (dec>5)
        dec=5;

    if (num<0)
        neg = 1;

    _convert_float(st, num, length, dec);

    if (divider != '.')
    {
        for (i=0; i<sizeof(st); i++)
            if (st[i]=='.')
                st[i]=divider;
    }

    if (filler != ' ')
    {
        if (neg)
        {
            st[0]='-';
            for (i=1; i<sizeof(st); i++)
                if ((st[i]==' ') || (st[i]=='-'))
                    st[i]=filler;
        }
        else
        {
            for (i=0; i<sizeof(st); i++)
                if (st[i]==' ')
                    st[i]=filler;
        }
    }

    Print(st,x,y,0);
}
*/

void SetFont(uint8_t* const cfont)
{
    font.font=(uint8_t*)cfont;
    font.x_size=fontbyte(0);
    font.y_size=fontbyte(1);
    font.offset=fontbyte(2);
    font.numchars=fontbyte(3);
}

uint8_t* GetFont()
{
    return font.font;
}

uint8_t GetFontXsize()
{
    return font.x_size;
}

uint8_t GetFontYsize()
{
    return font.y_size;
}

void DrawBitmap(int16_t x, int16_t y, int16_t sx, int16_t sy, bitmapdatatype data, int16_t scale)
{
    uint16_t col;
    int16_t tx, ty, tc, tsx, tsy;

    if (scale==1)
    {
        if (displayOrientation==enPortrait)
        {

            SetXY(x, y, x+sx-1, y+sy-1);
            for (tc=0; tc<(sx*sy); tc++)
            {
                col=pgm_read_word(&data[tc]);
                LCD_Write_Data16(col);
            }

        }
        else
        {

            for (ty=0; ty<sy; ty++)
            {
                SetXY(x, y+ty, x+sx-1, y+ty);
                for (tx=sx-1; tx>=0; tx--)
                {
                    col=pgm_read_word(&data[(ty*sx)+tx]);
                    LCD_Write_Data16(col);
                }
            }

        }
    }
    else
    {
        if (displayOrientation==enPortrait)
        {

            for (ty=0; ty<sy; ty++)
            {
                SetXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
                for (tsy=0; tsy<scale; tsy++)
                    for (tx=0; tx<sx; tx++)
                    {
                        col=pgm_read_word(&data[(ty*sx)+tx]);
                        for (tsx=0; tsx<scale; tsx++)
                            LCD_Write_Data16(col);
                    }
            }

        }
        else
        {

            for (ty=0; ty<sy; ty++)
            {
                for (tsy=0; tsy<scale; tsy++)
                {
                    SetXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
                    for (tx=sx-1; tx>=0; tx--)
                    {
                        col=pgm_read_word(&data[(ty*sx)+tx]);
                        for (tsx=0; tsx<scale; tsx++)
                            LCD_Write_Data16(col);
                    }
                }
            }

        }
    }
    ClrXY();
}
/*
void DrawBitmap(int16_t x, int16_t y, int16_t sx, int16_t sy, bitmapdatatype data, int16_t deg, int16_t rox, int16_t roy)
{
    uint16_t col;
    int16_t tx, ty, newx, newy;
    double radian;
    radian=deg*0.0175;

    if (deg==0)
        drawBitmap(x, y, sx, sy, data);
    else
    {

        for (ty=0; ty<sy; ty++)
            for (tx=0; tx<sx; tx++)
            {
                col=pgm_read_word(&data[(ty*sx)+tx]);

                newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
                newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

                SetXY(newx, newy, newx, newy);
                LCD_Write_Data16(col);
            }

    }
    ClrXY();
}
*/

int16_t GetDisplayXSize()
{
    if (displayOrientation==enPortrait)
        return display_size_x+1;
    else
        return display_size_y+1;
}

int16_t GetDisplayYSize()
{
    if (displayOrientation==enPortrait)
        return display_size_y+1;
    else
        return display_size_x+1;
}



//bool TSPoint::operator==(TSPoint p1) {
//  return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
//}
//
//bool TSPoint::operator!=(TSPoint p1) {
//  return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
//}

//#if (NUMSAMPLES > 2)
//static void insert_sort(int array[], uint8_t size) {
//  uint8_t j;
//  int save;
//
//  for (int i = 1; i < size; i++) {
//    save = array[i];
//    for (j = i; j >= 1 && save < array[j - 1]; j--)
//      array[j] = array[j - 1];
//    array[j] = save;
//  }
//}
//#endif
//
//TSPoint GetPoint(void) {
//    int16_t x, y, z;
//    int16_t samples[NUMSAMPLES];
//    uint8_t i, valid;
//
//    valid = 1;
//
//    SetPinAsInput(Y_PLUS_PORT, Y_PLUS_PIN);
//    SetPinAsInput(Y_MINUS_PORT, Y_MINUS_PIN);
//
//    SetLow(Y_PLUS_PORT, Y_PLUS_PIN);
//    SetLow(Y_MINUS_PORT, Y_MINUS_PIN);
//
//    SetPinAsOutput(X_PLUS_PORT, X_PLUS_PIN);
//    SetPinAsOutput(X_MINUS_PORT, X_MINUS_PIN);
//
//
//    SetHigh(X_PLUS_PORT, X_PLUS_PIN);
//    SetLow(X_MINUS_PORT, X_MINUS_PIN);
//
//    for (i=0; i<NUMSAMPLES; i++) {
//        samples[i] = analogRead(_yp);
//    }
//#if NUMSAMPLES > 2
//    insert_sort(samples, NUMSAMPLES);
//#endif
//#if NUMSAMPLES == 2
//    if (samples[0] != samples[1]) { valid = 0; }
//#endif
//    x = (1023-samples[NUMSAMPLES/2]);
//
//    pinMode(_xp, INPUT);
//    pinMode(_xm, INPUT);
//    *portOutputRegister(xp_port) &= ~xp_pin;
//
//
//    pinMode(_yp, OUTPUT);
//    *portOutputRegister(yp_port) |= yp_pin;
//
//    pinMode(_ym, OUTPUT);
//
//    for (i=0; i<NUMSAMPLES; i++) {
//        samples[i] = analogRead(_xm);
//    }
//
//#if NUMSAMPLES > 2
//    insert_sort(samples, NUMSAMPLES);
//#endif
//#if NUMSAMPLES == 2
//    if (samples[0] != samples[1]) { valid = 0; }
//#endif
//
//    y = (1023-samples[NUMSAMPLES/2]);
//
//    // Set X+ to ground
//    pinMode(_xp, OUTPUT);
//    *portOutputRegister(xp_port) &= ~xp_pin;
//    //digitalWrite(_xp, LOW);
//
//    // Set Y- to VCC
//    *portOutputRegister(ym_port) |= ym_pin;
//    //digitalWrite(_ym, HIGH);
//
//    // Hi-Z X- and Y+
//    *portOutputRegister(yp_port) &= ~yp_pin;
//    //digitalWrite(_yp, LOW);
//    pinMode(_yp, INPUT);
//
//    int z1 = analogRead(_xm);
//    int z2 = analogRead(_yp);
//
//    if (_rxplate != 0) {
//        // now read the x
//        float rtouch;
//        rtouch = z2;
//        rtouch /= z1;
//        rtouch -= 1;
//        rtouch *= x;
//        rtouch *= _rxplate;
//        rtouch /= 1024;
//
//        z = rtouch;
//    } else {
//        z = (1023-(z2-z1));
//    }
//
//    if (! valid) {
//        z = 0;
//    }
//
//    return TSPoint(x, y, z);
//}
//
////TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
////  _yp = yp;
////  _xm = xm;
////  _ym = ym;
////  _xp = xp;
////  _rxplate = 0;
////  pressureThreshhold = 10;
////}
//
//
////TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym,
////             uint16_t rxplate) {
////  _yp = yp;
////  _xm = xm;
////  _ym = ym;
////  _xp = xp;
////  _rxplate = rxplate;
////
////  pressureThreshhold = 10;
////}
//
//int ReadTouchX(void) {
//   pinMode(_yp, INPUT);
//   pinMode(_ym, INPUT);
//   digitalWrite(_yp, LOW);
//   digitalWrite(_ym, LOW);
//
//   pinMode(_xp, OUTPUT);
//   digitalWrite(_xp, HIGH);
//   pinMode(_xm, OUTPUT);
//   digitalWrite(_xm, LOW);
//
//   return (1023-analogRead(_yp));
//}
//
//
//int ReadTouchY(void) {
//   pinMode(_xp, INPUT);
//   pinMode(_xm, INPUT);
//   digitalWrite(_xp, LOW);
//   digitalWrite(_xm, LOW);
//
//   pinMode(_yp, OUTPUT);
//   digitalWrite(_yp, HIGH);
//   pinMode(_ym, OUTPUT);
//   digitalWrite(_ym, LOW);
//
//   return (1023-analogRead(_xm));
//}
//
//
//uint16_t Pressure(void) {
//  // Set X+ to ground
//  pinMode(_xp, OUTPUT);
//  digitalWrite(_xp, LOW);
//
//  // Set Y- to VCC
//  pinMode(_ym, OUTPUT);
//  digitalWrite(_ym, HIGH);
//
//  // Hi-Z X- and Y+
//  digitalWrite(_xm, LOW);
//  pinMode(_xm, INPUT);
//  digitalWrite(_yp, LOW);
//  pinMode(_yp, INPUT);
//
//  int z1 = analogRead(_xm);
//  int z2 = analogRead(_yp);
//
//  if (_rxplate != 0) {
//    // now read the x
//    float rtouch;
//    rtouch = z2;
//    rtouch /= z1;
//    rtouch -= 1;
//    rtouch *= readTouchX();
//    rtouch *= _rxplate;
//    rtouch /= 1024;
//
//    return rtouch;
//  } else {
//    return (1023-(z2-z1));
//  }
//}


