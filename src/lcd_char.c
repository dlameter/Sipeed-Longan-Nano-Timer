#include "lcd.h"
#include "lcd_char.h"
#include "bgcol.h"

int get_char_start(char c) {
    switch (c) {
        case '0':
            return CHAR_ARRAY_ONE_CHAR * 0;
        case '1':
            return CHAR_ARRAY_ONE_CHAR * 1;
        case '2':
            return CHAR_ARRAY_ONE_CHAR * 2;
        case '3':
            return CHAR_ARRAY_ONE_CHAR * 3;
        case '4':
            return CHAR_ARRAY_ONE_CHAR * 4;
        case '5':
            return CHAR_ARRAY_ONE_CHAR * 5;
        case '6':
            return CHAR_ARRAY_ONE_CHAR * 6;
        case '7':
            return CHAR_ARRAY_ONE_CHAR * 7;
        case '8':
            return CHAR_ARRAY_ONE_CHAR * 8;
        case '9':
            return CHAR_ARRAY_ONE_CHAR * 9;
        case ':':
            return CHAR_ARRAY_ONE_CHAR * 10;
        default:
            return CHAR_ARRAY_ONE_CHAR * 8;
    }
}

void draw_char(uint16_t  x, uint16_t y, char c, unsigned short int color, uint16_t* buffer) {
    int start = get_char_start(c);

    for (int i = 0; i < CHAR_WIDTH; i++) {
        for (int j = 0; j < CHAR_HEIGHT; j++) {
            int index = start + (i / 8) + (j * (CHAR_WIDTH / 8));
            int shift = (7 - (i % 8)) ;

            uint16_t* pixel = buffer + (x + i) + (LCD_WIDTH * (y + j));
            if ((characters[index] >> shift) & ~((~0u) << 1)) {
                *pixel = color;
            }
            else {
                *pixel = bgcolxy(x + i, y + j);
            }
        }
    }
}
