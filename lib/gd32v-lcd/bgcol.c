#include "bgcol.h"
#include "lcd.h"

uint16_t bgcolxy(int x, int y)
{
    x -= LCD_WIDTH >> 1;
    y -= LCD_HEIGHT >> 1;
    y <<= 1;
    int r = x*x + y*y;
    return r >> 11;
}

uint16_t bgcol(int p)
{
    int y = p / LCD_WIDTH;
    int x = p - y * LCD_WIDTH;
    return bgcolxy(x, y);
}
