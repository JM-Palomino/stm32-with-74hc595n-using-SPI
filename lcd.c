

#include "lcd.h"
#include "tim.h"
#include "i2c.h"
//------------------------------------------------
uint8_t buf[1]={0};
extern I2C_HandleTypeDef hi2c1;
//------------------------------------------------

//------------------------------------------------
void LCD_WriteByteI2CLCD(uint8_t bt)
{
	buf[0]=bt;
	HAL_I2C_Master_Transmit(&hi2c1,(uint16_t) 0x4E,buf,1,100);
}
//------------------------------------------------
void I2C_LCD_Cmd(char out_char) {

    uint8_t hi_n, lo_n;
    uint8_t rs = 0x00;

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    LCD_WriteByteI2CLCD(hi_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(hi_n | rs | 0x00 | 0x08);
    DelayMicro(100);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x00 | 0x08);

    if(out_char == 0x01) HAL_Delay(2);
}

//------------------------------------------------

void I2C_LCD_Chr(char row, uint8_t column, char out_char) {

     uint8_t hi_n, lo_n;
     uint8_t rs = 0x01;

    switch(row){

        case 1:
        I2C_LCD_Cmd(0x80 + (column - 1));
        break;
        case 2:
        I2C_LCD_Cmd(0xC0 + (column - 1));
        break;
        case 3:
        I2C_LCD_Cmd(0x94 + (column - 1));
        break;
        case 4:
        I2C_LCD_Cmd(0xD4 + (column - 1));
        break;
    };

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    LCD_WriteByteI2CLCD(hi_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(hi_n | rs | 0x00 | 0x08);
    DelayMicro(100);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x00 | 0x08);
}

void I2C_LCD_Chr_Cp(char out_char) {

     uint8_t hi_n, lo_n;
     uint8_t rs = 0x01;

    hi_n = out_char & 0xF0;
    lo_n = (out_char << 4) & 0xF0;

    LCD_WriteByteI2CLCD(hi_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(hi_n | rs | 0x00 | 0x08);
    DelayMicro(100);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(lo_n | rs | 0x00 | 0x08);
}

void I2C_LCD_Init() {

    uint8_t rs = 0x00;

    HAL_Delay(30);

    LCD_WriteByteI2CLCD(0x30 | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(0x30 | rs | 0x00 | 0x08);
    HAL_Delay(10);

    LCD_WriteByteI2CLCD(0x30 | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(0x30 | rs | 0x00 | 0x08);
    HAL_Delay(10);

    LCD_WriteByteI2CLCD(0x30 | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(0x30 | rs | 0x00 | 0x08);
    HAL_Delay(10);

    LCD_WriteByteI2CLCD(0x20 | rs | 0x04 | 0x08);
    DelayMicro(50);
    LCD_WriteByteI2CLCD(0x20 | rs | 0x00 | 0x08);
  

     HAL_Delay(10);

    I2C_LCD_Cmd(0x28);
    I2C_LCD_Cmd(0x06);
}

void I2C_LCD_Out(char row, uint8_t col, char*text) {
    while(*text) I2C_LCD_Chr(row, col++, *text++);       
}

void I2C_LCD_Out_Cp(char *text) {
    while(*text) 
		I2C_LCD_Chr_Cp(*text++);       
}
