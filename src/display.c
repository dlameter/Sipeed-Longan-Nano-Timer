#include "display.h"
#include "lcd/lcd.h"
#include "gd32vf103.h"

void display_int(int x, int y, int value) {
    int base = '0';
    int location = 0;
    const int char_size = 8;

    while (value != 0) {
        int digit = value % 10;
        LCD_ShowChar8(x - (char_size * location), y, base + digit, WHITE);
        location++;
        value /= 10;
    }
}

void display_time(int x, int y, int value) {
    int minute, minute_d1, minute_d2;
    int second, second_d1, second_d2;
    second = value / 1000;
    minute = second / 60;
    second = second % 60;
    minute = minute % 60;
    minute_d2 = minute % 10;
    minute_d1 = (minute / 10) % 10;
    second_d2 = second % 10;
    second_d1 = (second / 10) % 10;

    LCD_ShowChar8(x, y, '0' + minute_d1, WHITE);
    LCD_ShowChar8(x + 8, y, '0' + minute_d2, WHITE);
    LCD_ShowChar8(x + 16, y, ':', WHITE);
    LCD_ShowChar8(x + 24, y, '0' + second_d1, WHITE);
    LCD_ShowChar8(x + 32, y, '0' + second_d2, WHITE);
}
