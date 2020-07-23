#include "gd32vf103.h"
#include "gd32vf103v_lcd_eval.h"

int main() {
    // main entry file

    // Initialize the lcd
    exmc_lcd_init();

    lcd_clear(LCD_COLOR_GREEN);

    return 0;
}
