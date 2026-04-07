#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define LCD_EN P3_2
#define LCD_RS P3_3
     
#define LCD_D7 P1_0
#define LCD_D6 P1_1
#define LCD_D5 P1_2
#define LCD_D4 P1_3

#define LCD_BL P1_4

void initDisplay(void);
void clearDisplay(void);
void writeChar(uint8_t);
void writeLine(uint8_t*);
void newLine(void);
void wait1s(void);

void wait50micro(void);         // delay 50 mikrosekundi
void lcd_set_cursor(uint8_t row, uint8_t col);  // postavi kursor


#endif