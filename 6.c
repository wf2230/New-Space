/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 2016/11/15
Author  :
Company :
Comments:


Chip type               : ATxmega32A4U
Program type            : Application
AVR Core Clock frequency: 2.000000 MHz
Memory model            : Small
Data Stack size         : 1024
*******************************************************/

// I/O Registers definitions
#include <io.h>
#include <stdlib.h>
// Standard Input/Output functions
#include <stdio.h>
#include <delay.h>
#include <string.h>
// on the graphic display
#include <font5x7.h>
#include <pcb37_lcd.h>
#include <string.h>
#include <math.h>
// Graphic Display functions
#include <glcd.h>

// Font used for displaying text
// on the graphic display
#include <font5x7.h>

unsigned int adca_read_AVG(unsigned char channel);

// Declare your global variables here
unsigned char income[40],dataread[4],out[4];

char display_buffer[4], s1[10];
unsigned int data_count;
float con, temp;
int test[40],gf_sn1,wow=0,check_high[2],check_low[2],send1, suss1, fail1;;


flash unsigned char welcome[]=
{
/* Image width: 18 pixels */
0x12, 0x00,
/* Image height: 14 pixels */
0x0E, 0x00,
#ifndef _GLCD_DATA_BYTEY_
/* Image data for monochrome displays organized
   as horizontal rows of bytes */
0xE9, 0x01, 0x00, 0x29, 0x01, 0x00, 0x29, 0x01,
0x01, 0xEF, 0xC1, 0x00, 0x00, 0x21, 0x00, 0xE0,
0x99, 0x03, 0x00, 0x04, 0x02, 0x00, 0x83, 0x03,
0x80, 0x00, 0x02, 0x60, 0x84, 0x03, 0x10, 0x7C,
0x00, 0x0C, 0x54, 0x00, 0x02, 0x54, 0x00, 0x00,
0x54, 0x00,
#else
/* Image data for monochrome displays organized
   as rows of vertical bytes */
0x0F, 0x08, 0x08, 0x0F, 0x00, 0x2F, 0x29, 0x29,
0xBF, 0x80, 0x40, 0x20, 0x20, 0x10, 0x08, 0xA8,
0xA4, 0xE0, 0x00, 0x10, 0x08, 0x08, 0x04, 0x02,
0x02, 0x01, 0x00, 0x00, 0x3E, 0x04, 0x3C, 0x04,
0x3C, 0x02, 0x02, 0x03,
#endif
};



//¥H¤U¬°¦r«¬¸ê®Æ
eeprom unsigned char FONT_NUM16x11_U[11][11]=   //16x11ªº¦r«¬ 0-9­Ó ¤W¥b³¡
   {
     {0xFC, 0xFE, 0xFE, 0x0F, 0x07, 0x07, 0x0F, 0xFE,  0xFE, 0xFC, 0x00},   // 0
     {0x00, 0x00, 0x1C, 0x1E, 0xFF, 0xFF, 0xFF, 0x00,  0x00, 0x00, 0x00},   // 1
     {0x1C, 0x1E, 0x9E, 0x8F, 0xC7, 0xC7, 0xEF, 0xFE,  0xFE, 0x78, 0x00},   // 2
     {0x1C, 0x0E, 0x07, 0x07, 0xE7, 0xE7, 0xE7, 0xFF,  0xFE, 0x3C, 0x00},   // 3
     {0xC0, 0xF0, 0xF8, 0x3C, 0x0E, 0x07, 0xFF, 0xFF,  0xFF, 0x00, 0x00},   // 4
     {0x7F, 0x7F, 0x7F, 0x67, 0x67, 0x67, 0x67, 0xE7,  0xE7, 0xC0, 0x00},   // 5
     {0xF0, 0xFC, 0xFC, 0xCE, 0xE6, 0xE7, 0xE3, 0xC1,  0xC0, 0x00, 0x00},   // 6
     {0x07, 0x07, 0x07, 0x87, 0xC7, 0xE7, 0xFF, 0xFF,  0x3F, 0x1F, 0x00},   // 7
     {0x1C, 0xBE, 0xFE, 0xCF, 0xC7, 0xC7, 0xCF, 0xFE,  0xBE, 0x1C, 0x00},   // 8
     {0x38, 0xFE, 0xFE, 0xCF, 0xC7, 0xC7, 0xCF, 0xFE,  0xFC, 0xF8, 0x00},   // 9
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00}};   //sp
eeprom unsigned char FONT_NUM16x11_D[11][11]=   //16x11ªº¦r«¬ 0-9­Ó ¤U¥b³¡
   {
    { 0x0F, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x3C, 0x1F,  0x1F, 0x0F, 0x00},   // 0
    { 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00,  0x00, 0x00, 0x00},   // 1
    { 0x3C, 0x3F, 0x3F, 0x3B, 0x39, 0x39, 0x39, 0x38,  0x38, 0x38, 0x00},   // 2
    { 0x0E, 0x1E, 0x3C, 0x38, 0x38, 0x38, 0x38, 0x3F,  0x1F, 0x0F, 0x00},   // 3
    { 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x3F, 0x3F,  0x3F, 0x07, 0x00},   // 4
    { 0x1E, 0x1E, 0x3E, 0x38, 0x38, 0x38, 0x38, 0x3F,  0x1F, 0x0F, 0x00},   // 5
    { 0x07, 0x0F, 0x1F, 0x3C, 0x38, 0x38, 0x3C, 0x1F,  0x1F, 0x07, 0x00},   // 6
    { 0x00, 0x3C, 0x3F, 0x3F, 0x3F, 0x0F, 0x01, 0x00,  0x00, 0x00, 0x00},   // 7
    { 0x0F, 0x1F, 0x1F, 0x3C, 0x38, 0x38, 0x3C, 0x1F,  0x1F, 0x0F, 0x00},   // 8
    { 0x00, 0x00, 0x20, 0x31, 0x39, 0x19, 0x1C, 0x0F,  0x0F, 0x03, 0x00},   // 9
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00}};   //sp

unsigned char FONT5x7_1[91][5]=
{
    { 0x00, 0x00, 0x00, 0x00, 0x00 },  // sp
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x23, 0x13, 0x08, 0x64, 0x62 },   // %
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   // ,
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   // -
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y
    { 0x44, 0x64, 0x54, 0x4C, 0x44 }    // z
};


// System Clocks initialization
void system_clocks_init(void)
{
unsigned char n,s;

// Optimize for speed
#pragma optsize-
// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// Internal 2 MHz RC oscillator initialization
// Enable the internal 2 MHz RC oscillator
OSC.CTRL|=OSC_RC2MEN_bm;

// System Clock prescaler A division factor: 1
// System Clock prescalers B & C division factors: B:1, C:1
// ClkPer4: 2000.000 kHz
// ClkPer2: 2000.000 kHz
// ClkPer:  2000.000 kHz
// ClkCPU:  2000.000 kHz
n=(CLK.PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm | CLK_PSBCDIV0_bm))) |
	CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc;
CCP=CCP_IOREG_gc;
CLK.PSCTRL=n;

// Disable the auto-calibration of the internal 2 MHz RC oscillator
DFLLRC2M.CTRL&= ~DFLL_ENABLE_bm;

// Wait for the internal 2 MHz RC oscillator to stabilize
while ((OSC.STATUS & OSC_RC2MRDY_bm)==0);

// Select the system clock source: 2 MHz Internal RC Osc.
n=(CLK.CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC2M_gc;
CCP=CCP_IOREG_gc;
CLK.CTRL=n;

// Disable the unused oscillators: 32 MHz, 32 kHz, external clock/crystal oscillator, PLL
OSC.CTRL&= ~(OSC_RC32MEN_bm | OSC_RC32KEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm);

// ClkPer output disabled
PORTCFG.CLKEVOUT&= ~(PORTCFG_CLKOUTSEL_gm | PORTCFG_CLKOUT_gm);
// Restore interrupts enabled/disabled state
SREG=s;
// Restore optimization for size if needed
#pragma optsize_default
}

// Event System initialization
void event_system_init(void)
{
// Event System Channel 0 source: None
EVSYS.CH0MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 1 source: None
EVSYS.CH1MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 2 source: None
EVSYS.CH2MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 3 source: None
EVSYS.CH3MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 4 source: None
EVSYS.CH4MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 5 source: None
EVSYS.CH5MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 6 source: None
EVSYS.CH6MUX=EVSYS_CHMUX_OFF_gc;
// Event System Channel 7 source: None
EVSYS.CH7MUX=EVSYS_CHMUX_OFF_gc;

// Event System Channel 0 Digital Filter Coefficient: 1 Sample
// Quadrature Decoder: Off
EVSYS.CH0CTRL=(EVSYS.CH0CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
	EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 1 Digital Filter Coefficient: 1 Sample
EVSYS.CH1CTRL=EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 2 Digital Filter Coefficient: 1 Sample
// Quadrature Decoder: Off
EVSYS.CH2CTRL=(EVSYS.CH2CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
	EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 3 Digital Filter Coefficient: 1 Sample
EVSYS.CH3CTRL=EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 4 Digital Filter Coefficient: 1 Sample
// Quadrature Decoder: Off
EVSYS.CH4CTRL=(EVSYS.CH4CTRL & (~(EVSYS_QDIRM_gm | EVSYS_QDIEN_bm | EVSYS_QDEN_bm | EVSYS_DIGFILT_gm))) |
	EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 5 Digital Filter Coefficient: 1 Sample
EVSYS.CH5CTRL=EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 6 Digital Filter Coefficient: 1 Sample
EVSYS.CH6CTRL=EVSYS_DIGFILT_1SAMPLE_gc;
// Event System Channel 7 Digital Filter Coefficient: 1 Sample
EVSYS.CH7CTRL=EVSYS_DIGFILT_1SAMPLE_gc;

// Event System Channel output: Disabled
PORTCFG.CLKEVOUT&= ~PORTCFG_EVOUT_gm;
PORTCFG.EVOUTSEL&= ~PORTCFG_EVOUTSEL_gm;
}

// Ports initialization
void ports_init(void)
{
// PORTA initialization
// OUT register
PORTA.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTA.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTA.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTA.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTA.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTA.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTA.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTA.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTA.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTA.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTA.INTCTRL=(PORTA.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTA.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTA.INT1MASK=0x00;

// PORTB initialization
// OUT register
PORTB.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
PORTB.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTB.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTB.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTB.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTB.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTB.INTCTRL=(PORTB.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
PORTB.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
PORTB.INT1MASK=0x00;

// PORTC initialization
// OUT register
PORTC.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTC.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTC.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTC.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTC.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTC.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTC.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTC.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTC.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTC.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// PORTC Peripheral Output Remapping
// OC0A Output: Pin 0
// OC0B Output: Pin 1
// OC0C Output: Pin 2
// OC0D Output: Pin 3
// USART0 XCK: Pin 1
// USART0 RXD: Pin 2
// USART0 TXD: Pin 3
// SPI MOSI: Pin 5
// SPI SCK: Pin 7
PORTC.REMAP=(0<<PORT_SPI_bp) | (0<<PORT_USART0_bp) | (0<<PORT_TC0D_bp) | (0<<PORT_TC0C_bp) | (0<<PORT_TC0B_bp) | (0<<PORT_TC0A_bp);
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTC.INTCTRL=(PORTC.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTC.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTC.INT1MASK=0x00;

// PORTD initialization
// OUT register
PORTD.OUT=0x08;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Output
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTD.DIR=0xFF;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTD.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTD.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTD.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTD.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin4 Output/Pull configuration: Totempole/No
// Pin4 Input/Sense configuration: Sense both edges
// Pin4 Inverted: Off
// Pin4 Slew Rate Limitation: Off
PORTD.PIN4CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin5 Output/Pull configuration: Totempole/No
// Pin5 Input/Sense configuration: Sense both edges
// Pin5 Inverted: Off
// Pin5 Slew Rate Limitation: Off
PORTD.PIN5CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin6 Output/Pull configuration: Totempole/No
// Pin6 Input/Sense configuration: Sense both edges
// Pin6 Inverted: Off
// Pin6 Slew Rate Limitation: Off
PORTD.PIN6CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin7 Output/Pull configuration: Totempole/No
// Pin7 Input/Sense configuration: Sense both edges
// Pin7 Inverted: Off
// Pin7 Slew Rate Limitation: Off
PORTD.PIN7CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTD.INTCTRL=(PORTD.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
// Pin4 Pin Change interrupt 0: Off
// Pin5 Pin Change interrupt 0: Off
// Pin6 Pin Change interrupt 0: Off
// Pin7 Pin Change interrupt 0: Off
PORTD.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
// Pin4 Pin Change interrupt 1: Off
// Pin5 Pin Change interrupt 1: Off
// Pin6 Pin Change interrupt 1: Off
// Pin7 Pin Change interrupt 1: Off
PORTD.INT1MASK=0x00;

// PORTE initialization
// OUT register
PORTE.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
PORTE.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTE.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTE.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin2 Output/Pull configuration: Totempole/No
// Pin2 Input/Sense configuration: Sense both edges
// Pin2 Inverted: Off
// Pin2 Slew Rate Limitation: Off
PORTE.PIN2CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin3 Output/Pull configuration: Totempole/No
// Pin3 Input/Sense configuration: Sense both edges
// Pin3 Inverted: Off
// Pin3 Slew Rate Limitation: Off
PORTE.PIN3CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTE.INTCTRL=(PORTE.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
// Pin2 Pin Change interrupt 0: Off
// Pin3 Pin Change interrupt 0: Off
PORTE.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
// Pin2 Pin Change interrupt 1: Off
// Pin3 Pin Change interrupt 1: Off
PORTE.INT1MASK=0x00;

// PORTR initialization
// OUT register
PORTR.OUT=0x00;
// Pin0: Input
// Pin1: Input
PORTR.DIR=0x00;
// Pin0 Output/Pull configuration: Totempole/No
// Pin0 Input/Sense configuration: Sense both edges
// Pin0 Inverted: Off
// Pin0 Slew Rate Limitation: Off
PORTR.PIN0CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Pin1 Output/Pull configuration: Totempole/No
// Pin1 Input/Sense configuration: Sense both edges
// Pin1 Inverted: Off
// Pin1 Slew Rate Limitation: Off
PORTR.PIN1CTRL=PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc;
// Interrupt 0 level: Disabled
// Interrupt 1 level: Disabled
PORTR.INTCTRL=(PORTR.INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
	PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc;
// Pin0 Pin Change interrupt 0: Off
// Pin1 Pin Change interrupt 0: Off
PORTR.INT0MASK=0x00;
// Pin0 Pin Change interrupt 1: Off
// Pin1 Pin Change interrupt 1: Off
PORTR.INT1MASK=0x00;
}

// Virtual Ports initialization
void vports_init(void)
{
// PORTA mapped to VPORT0
// PORTB mapped to VPORT1
PORTCFG.VPCTRLA=PORTCFG_VP13MAP_PORTB_gc | PORTCFG_VP02MAP_PORTA_gc;
// PORTC mapped to VPORT2
// PORTD mapped to VPORT3
PORTCFG.VPCTRLB=PORTCFG_VP13MAP_PORTD_gc | PORTCFG_VP02MAP_PORTC_gc;
}

// USARTD0 initialization
void usartd0_init(void)
{
// Note: The correct PORTD direction for the RxD, TxD and XCK signals
// is configured in the ports_init function.

// Transmitter is enabled
// Set TxD=1
PORTD.OUTSET=0x08;

// Communication mode: Asynchronous USART
// Data bits: 8
// Stop bits: 1
// Parity: Disabled
USARTD0.CTRLC=USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;

// Receive complete interrupt: Low Level
// Transmit complete interrupt: Disabled
// Data register empty interrupt: Disabled
USARTD0.CTRLA=(USARTD0.CTRLA & (~(USART_RXCINTLVL_gm | USART_TXCINTLVL_gm | USART_DREINTLVL_gm))) |
	USART_RXCINTLVL_LO_gc | USART_TXCINTLVL_OFF_gc | USART_DREINTLVL_OFF_gc;

// Required Baud rate: 38400
// Real Baud Rate: 38415.4 (x2 Mode), Error: 0.0 %
USARTD0.BAUDCTRLA=0xC1;
USARTD0.BAUDCTRLB=((0x09 << USART_BSCALE_gp) & USART_BSCALE_gm) | 0x02;

// Receiver: On
// Transmitter: On
// Double transmission speed mode: On
// Multi-processor communication mode: Off
USARTD0.CTRLB=(USARTD0.CTRLB & (~(USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm | USART_MPCM_bm | USART_TXB8_bm))) |
	USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm;
}

// USARTD0 Receiver buffer
#define RX_BUFFER_SIZE_USARTD0 8
char rx_buffer_usartd0[RX_BUFFER_SIZE_USARTD0];

#if RX_BUFFER_SIZE_USARTD0 <= 256
unsigned char rx_wr_index_usartd0=0,rx_rd_index_usartd0=0;
#else
unsigned int rx_wr_index_usartd0=0,rx_rd_index_usartd0=0;
#endif

#if RX_BUFFER_SIZE_USARTD0 < 256
unsigned char rx_counter_usartd0=0;
#else
unsigned int rx_counter_usartd0=0;
#endif

// This flag is set on USARTD0 Receiver buffer overflow
bit rx_buffer_overflow_usartd0=0;

// USARTD0 Receiver interrupt service routine
interrupt [USARTD0_RXC_vect] void usartd0_rx_isr(void)
{
unsigned char status;
char data;

status=USARTD0.STATUS;
data=USARTD0.DATA;
putchar(data);
if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0)
   {
   rx_buffer_usartd0[rx_wr_index_usartd0++]=data;
#if RX_BUFFER_SIZE_USARTD0 == 256
   // special case for receiver buffer size=256
   if (++rx_counter_usartd0 == 0) rx_buffer_overflow_usartd0=1;
#else
   if (rx_wr_index_usartd0 == RX_BUFFER_SIZE_USARTD0) rx_wr_index_usartd0=0;
   if (++rx_counter_usartd0 == RX_BUFFER_SIZE_USARTD0)
      {
      rx_counter_usartd0=0;
      rx_buffer_overflow_usartd0=1;
      }
#endif
   }
}

// Receive a character from USARTD0
// USARTD0 is used as the default input device by the 'getchar' function
#define _ALTERNATE_GETCHAR_

#pragma used+
char getchar(void)
{
char data;

while (rx_counter_usartd0==0);
data=rx_buffer_usartd0[rx_rd_index_usartd0++];
#if RX_BUFFER_SIZE_USARTD0 != 256
if (rx_rd_index_usartd0 == RX_BUFFER_SIZE_USARTD0) rx_rd_index_usartd0=0;
#endif
#asm("cli")
--rx_counter_usartd0;
#asm("sei")
return data;
}
#pragma used-

// Write a character to the USARTD0 Transmitter
// USARTD0 is used as the default output device by the 'putchar' function
#define _ALTERNATE_PUTCHAR_

#pragma used+
void putchar(char c)
{
while ((USARTD0.STATUS & USART_DREIF_bm) == 0);
USARTD0.DATA=c;
}
#pragma used-

void CallSensor()
{
unsigned char buf[7]={0x10, 0x13, 0x2C, 0x10, 0x1F, 0x00, 0x7E};
int i;

      data_count = 0;
      for (i=0;i<7;++i)				//Send Message by uart to the outerworld
	  {
        //x=buf[i];
	    putchar(buf[i]);
	  }
}

void ReadSensor()
{
int i;
      for (i=0;i<55;++i)				//Send Message by uart to the outerworld
	  {
	    check_low[0]=check_low[0]+income[i];
	  }
      check_low[1]=(unsigned char)check_low[0];
      //test[2]=check_low;
      check_high[0]=check_low[0] >> 8;
      check_high[1]=(unsigned char)check_high[0];


if (check_low[1]==income[56]) // check_high[1]==income[37] &&     //&& check_high==income[37]    check_low[5]==income[38]
{
      suss1=suss1+1;
      wow=0;
      dataread[0]=income[19];
      dataread[1]=income[20];
      dataread[2]=income[21];
      dataread[3]=income[22];
      con = *(float *)&dataread;
      con=con*10;

      out[0]=income[23];
      out[1]=income[24];
      out[2]=income[25];
      out[3]=income[26];
      temp = *(float *)&out;
      temp=temp*10;
}
else
{
fail1=fail1+1;
wow=1;
}
check_high[0]=0;
check_high[1]=0;
check_low[0]=0;
check_low[1]=0;
}


//void ReadSensor()
//{
//int i;
//      for (i=0;i<56;++i)				//Send Message by uart to the outerworld
//	  {
//	    check_low[0]=check_low[0]+income[i];
//	  }
//      //check_low[1]=(unsigned char)check_low[0];
//      //test[2]=check_low;
//      //check_high[0]=check_low[0] >> 8;
//      //check_high[1]=(unsigned char)check_high[0];
//
//      check_high[1]=(income[55]<<8)|(income[56]);
//
//
//
//if (check_high[1]==check_low[0]) // check_high[1]==income[37] &&     //&& check_high==income[37]    check_low[5]==income[38]
//{
//      suss1=suss1+1;
//      wow=0;
//      dataread[0]=income[19];
//      dataread[1]=income[20];
//      dataread[2]=income[21];
//      dataread[3]=income[22];
//      con = *(float *)&dataread;
//      con=con*10;
//
//      out[0]=income[23];
//      out[1]=income[24];
//      out[2]=income[25];
//      out[3]=income[26];
//      temp = *(float *)&out;
//      temp=temp*10;
//
//}
//check_high[0]=0;
//check_high[1]=0;
//check_low[0]=0;
//check_low[1]=0;
//}

// RTC initialization
void rtcxm_init(void)
{
unsigned char s;

// RTC clock source: 32.768 kHz from internal RC Oscillator
// Select the clock source and enable the RTC clock
CLK.RTCCTRL=(CLK.RTCCTRL & (~CLK_RTCSRC_gm)) | CLK_RTCSRC_RCOSC32_gc | CLK_RTCEN_bm;
// Make sure that the RTC is stopped before initializing it
RTC.CTRL=RTC_PRESCALER_OFF_gc;

// Optimize for speed
#pragma optsize-
// Save interrupts enabled/disabled state
s=SREG;
// Disable interrupts
#asm("cli")

// Wait until the RTC is not busy
while (RTC.STATUS & RTC_SYNCBUSY_bm);
// Set the RTC period register
RTC.PER=0x0800;
// Set the RTC count register
RTC.CNT=0x0000;
// Set the RTC compare register
RTC.COMP=0x0000;

// Restore interrupts enabled/disabled state
SREG=s;
// Restore optimization for size if needed
#pragma optsize_default

// Set the clock prescaler: RTC Clock/1
// and start the RTC
RTC.CTRL=RTC_PRESCALER_DIV1_gc;

// RTC Clock output disabled
PORTCFG.CLKEVOUT&= ~PORTCFG_RTCOUT_bm;

// RTC overflow interrupt: Low Level
// RTC compare interrupt: Disabled
RTC.INTCTRL=RTC_OVFINTLVL_LO_gc | RTC_COMPINTLVL_OFF_gc;
}

// RTC overflow interrupt service routine
interrupt [RTC_OVF_vect] void rtcxm_overflow_isr(void)
{
gf_sn1 = adca_read_AVG(0);                     //ÅªAct (BankA-CH0)(PA1)
}





// Function used to read the calibration byte from the
// signature row, specified by 'index'
#pragma optsize-
unsigned char read_calibration_byte(unsigned char index)
{
unsigned char r;
NVM.CMD=NVM_CMD_READ_CALIB_ROW_gc;
r=*((flash unsigned char*) index);
// Clean up NVM command register
NVM.CMD=NVM_CMD_NO_OPERATION_gc;
return r;
}
#pragma optsize_default


// ADCA initialization
void adca_init(void)
{
// ADCA is enabled
// Resolution: 12 Bits
// Load the calibration value for 12 Bit resolution
// from the signature row
ADCA.CALL=read_calibration_byte(PROD_SIGNATURES_START+ADCACAL0_offset);
ADCA.CALH=read_calibration_byte(PROD_SIGNATURES_START+ADCACAL1_offset);

// Free Running mode: Off
// Gain stage impedance mode: High-impedance sources
// Current consumption: No limit
// Conversion mode: Unsigned
ADCA.CTRLB=(0<<ADC_IMPMODE_bp) | ADC_CURRLIMIT_NO_gc | (0<<ADC_CONMODE_bp) | ADC_RESOLUTION_12BIT_gc;

// Clock frequency: 500.000 kHz
ADCA.PRESCALER=ADC_PRESCALER_DIV32_gc;

// Reference: AREF pin on PORTA
// Temperature reference: On
ADCA.REFCTRL=ADC_REFSEL_AREFA_gc | (1<<ADC_TEMPREF_bp) | (0<<ADC_BANDGAP_bp);

// Initialize the ADC Compare register
ADCA.CMPL=0x00;
ADCA.CMPH=0x00;

// ADC channel 0 gain: 1
// ADC channel 0 input mode: Single-ended positive input signal
ADCA.CH0.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;

// ADC channel 0 positive input: ADC1 pin
// ADC channel 0 negative input: GND
ADCA.CH0.MUXCTRL=ADC_CH_MUXPOS_PIN1_gc;

// ADC channel 1 gain: 1
// ADC channel 1 input mode: Single-ended positive input signal
ADCA.CH1.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;

// ADC channel 1 positive input: ADC2 pin
// ADC channel 1 negative input: GND
ADCA.CH1.MUXCTRL=ADC_CH_MUXPOS_PIN2_gc;

// ADC channel 2 gain: 1
// ADC channel 2 input mode: Single-ended positive input signal
ADCA.CH2.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;

// ADC channel 2 positive input: ADC3 pin
// ADC channel 2 negative input: GND
ADCA.CH2.MUXCTRL=ADC_CH_MUXPOS_PIN3_gc;

// ADC channel 3 gain: 1
// ADC channel 3 input mode: Single-ended positive input signal
ADCA.CH3.CTRL=(0<<ADC_CH_START_bp) | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;

// ADC channel 3 positive input: ADC4 pin
// ADC channel 3 negative input: GND
ADCA.CH3.MUXCTRL=ADC_CH_MUXPOS_PIN4_gc;

// AD conversion is started by software
ADCA.EVCTRL=ADC_EVACT_NONE_gc;

// Channel 0 interrupt: Disabled
ADCA.CH0.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
// Channel 1 interrupt: Disabled
ADCA.CH1.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
// Channel 2 interrupt: Disabled
ADCA.CH2.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;
// Channel 3 interrupt: Disabled
ADCA.CH3.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_OFF_gc;

// Enable the ADC
ADCA.CTRLA|=ADC_ENABLE_bm;
// Insert a delay to allow the ADC common mode voltage to stabilize
delay_us(2);
}

// ADCA channel data read function using polled mode
unsigned int adca_read(unsigned char channel)
{
ADC_CH_t *pch=&ADCA.CH0+channel;
unsigned int data;

// Start the AD conversion
pch->CTRL|= 1<<ADC_CH_START_bp;
// Wait for the AD conversion to complete
while ((pch->INTFLAGS & ADC_CH_CHIF_bm)==0);
// Clear the interrupt flag
pch->INTFLAGS=ADC_CH_CHIF_bm;
// Read the AD conversion result
((unsigned char *) &data)[0]=pch->RESL;
((unsigned char *) &data)[1]=pch->RESH;
return data;
}

// ADCA sweeped channel(s) data read function
// for software triggered mode
void adca_sweep_read(unsigned char nch, unsigned int *pdata)
{
ADC_CH_t *pch=&ADCA.CH0;
unsigned char i,j,m;

// Sweep starts with channel 0
j=ADC_CH0START_bm;
// Prepare the AD conversion start mask for the sweeped channel(s)
m=0;
i=0;
do
  {
  m|=j;
  j<<=1;
  }
while (++i<nch);
// Ensure the interrupt flags are cleared
ADCA.INTFLAGS=ADCA.INTFLAGS;
// Start the AD conversion for the sweeped channel(s)
ADCA.CTRLA=(ADCA.CTRLA & (ADC_DMASEL_gm | ADC_FLUSH_bm | ADC_ENABLE_bm)) | m;
// Read and store the AD conversion results for all the sweeped channels
for (i=0; i<nch; i++)
    {
    // Wait for the AD conversion to complete
    while ((pch->INTFLAGS & ADC_CH_CHIF_bm)==0);
    // Clear the interrupt flag
    pch->INTFLAGS=ADC_CH_CHIF_bm;
    // Read the AD conversion result
    ((unsigned char *) pdata)[0]=pch->RESL;
    ((unsigned char *) pdata)[1]=pch->RESH;
    pdata++;
    pch++;
    }
}





void main(void)
{
// Declare your local variables here
unsigned char n;
     char DATA_21[]=" CH4", DATA_22[]="C3H6", DATA_23[]="SPAN",
          DATA_31[]="TEMP", DATA_32[]="REF", DATA_33[]="CutV",
          DATA_51[]="ACTO",DATA_52[]="REFO", DATA_53[]=" PPM";
unsigned int s2=0;

// Variable used to store Graphic Display
// controller initialization data
GLCDINIT_t glcd_init_data;

// Interrupt system initialization
// Optimize for speed
#pragma optsize-
// Make sure the interrupts are disabled
#asm("cli")
// Low level interrupt: On
// Round-robin scheduling for low level interrupt: Off
// Medium level interrupt: Off
// High level interrupt: Off
// The interrupt vectors will be placed at the start of the Application FLASH section
n=(PMIC.CTRL & (~(PMIC_RREN_bm | PMIC_IVSEL_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm))) |
	PMIC_LOLVLEN_bm;
CCP=CCP_IOREG_gc;
PMIC.CTRL=n;
// Set the default priority for round-robin scheduling
PMIC.INTPRI=0x00;
// Restore optimization for size if needed
#pragma optsize_default

// System clocks initialization
system_clocks_init();

// Event system initialization
event_system_init();

// Ports initialization
ports_init();

// Virtual Ports initialization
vports_init();

// USARTD0 initialization
usartd0_init();

// RTC initialization
rtcxm_init();

// ADCA initialization
adca_init();

// Graphic Display Controller initialization
// The PCD8544 connections are specified in the
// Project|Configure|C Compiler|Libraries|Graphic Display menu:
// SDIN - PORTC Pin 5
// SCLK - PORTC Pin 7
// D /C - PORTC Pin 2
// /SCE - PORTC Pin 4
// /RES - PORTC Pin 3

// Specify the current font for displaying text
//glcd_init_data.font=font5x7;
// No function is used for reading
// image data from external memory
glcd_init_data.readxmem=NULL;
// No function is used for writing
// image data to external memory
glcd_init_data.writexmem=NULL;
// Set the LCD temperature coefficient
glcd_init_data.temp_coef=PCD8544_DEFAULT_TEMP_COEF;
// Set the LCD bias
glcd_init_data.bias=PCD8544_DEFAULT_BIAS;
// Set the LCD contrast control voltage VLCD
//glcd_init_data.vlcd=PCD8544_DEFAULT_VLCD;
glcd_init_data.vlcd=67;
glcd_init(&glcd_init_data);
pcd8544_wrcmd(0x2E);
glcd_setfont(font5x7);

printf("CLEARDATA\r\n");
delay_ms(50); 
printf("LABEL,Date,Time,Voltage\r\n");
delay_ms(50); 

// Globally enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      printf("DATA,DATE,TIME,");
      printf("%d\r\n",s2); 
      delay_ms(1000);
      s2++;

      }
}

unsigned int adca_read_AVG(unsigned char channel)
  {
    unsigned char avg=1,b=0;
    float data1=0;
    unsigned int data=0;
    for(b=0;b<30;b++)
       {
         if(data1==0)
           {adca_read(channel);}
         data1 = (data1+(float)adca_read(channel))/2;
       }
    if(data1>=188)
      {data1=data1-188;;}     //¹ê´úµ²ªG(05/27) ¦h¤F188AD
    else
      {data1=0;}
    data=(unsigned int)data1;

    return data;
  }