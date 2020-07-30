#include "gd32vf103.h"
#include "display.h"
#include "lcd.h"
#include "lcd_char.h"

void display_time(int x, int y, int value, uint16_t* buffer) {
    int minute, second; 
    second = value / 1000;
    minute = second / 60;
    second = second % 60;
    minute = minute % 60;

    draw_char(x, y, '0' + ((minute / 10) % 10), 0xffff, buffer);
    draw_char(x + CHAR_WIDTH, y, '0' + (minute % 10), 0xffff, buffer);
    draw_char(x + CHAR_WIDTH * 2, y, ':', 0xffff, buffer);
    draw_char(x + CHAR_WIDTH * 3, y, '0' + ((second / 10) % 10), 0xffff, buffer);
    draw_char(x + CHAR_WIDTH * 4, y, '0' + (second % 10), 0xffff, buffer);
}
