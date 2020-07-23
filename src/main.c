#include "gd32vf103.h"

int main() {
    // main entry file

    // Initialize the lcd
    exmc_lcd_init();
    lcd_init();

    lcd_clear(LCD_COLOR_GREEN);

    while(0) {};

    return 0;
}
