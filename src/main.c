#include "gd32vf103.h"
#include "lcd/lcd.h"

int main() {
    // main entry file

    // LCD init
    Lcd_Init();
    LCD_Clear(BLUE);

    while(1);

    return 0;
}
