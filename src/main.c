#include "gd32vf103.h"
#include "lcd/lcd.h"

#define TIMER_DURATION 90000

uint64_t timer_start() {
    uint64_t time, tmp;

    tmp = get_timer_value();
    do {
        time = get_timer_value();
    } while (time == tmp);

    return time;
}

int timer_diff_in_milliseconds(uint64_t time) {
    uint64_t delta_time = get_timer_value() - time;
    
    return (int) delta_time / 20000;
}

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

int main() {
    // main entry file

    // LCD init
    Lcd_Init();
    LCD_Clear(BLUE);


    // Start timer
    uint64_t start = timer_start();
    while(1) {
        LCD_Clear(BLUE);

        display_int(8 * 16, 16, timer_diff_in_milliseconds(start));
        display_time(8 * 12, 24, TIMER_DURATION - timer_diff_in_milliseconds(start));

        // Draw characters on screen
        // position goes by pixel and text is 8px by 8px
        LCD_ShowChar8(0, 0, 'T', WHITE);
        LCD_ShowChar8(8, 8, 'L', WHITE);

        delay_1ms(100);
    }

    return 0;
}
