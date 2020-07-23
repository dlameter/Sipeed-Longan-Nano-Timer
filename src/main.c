#include "gd32vf103.h"
#include "display.h"
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

int main() {
    // LCD init
    u16 background_color = BLUE;
    Lcd_Init();
    LCD_Clear(background_color);

    // Init gpio for BOOT0 button that responds on PA8 after boot.
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    // State of BOOT0 button
    uint16_t button;

    // timer
    uint64_t start = timer_start();

    // State of timer
    uint16_t triggered = 1;
    int timer_diff = TIMER_DURATION;

    while(1) {
        LCD_Clear(background_color);

        // If the timer is not triggered do a countdown
        if (!triggered) {
            timer_diff = timer_diff_in_milliseconds(start);

            if (TIMER_DURATION - timer_diff <= 0) {
                triggered = 1;
                timer_diff = TIMER_DURATION;
            }
        }
        else {
            if (background_color == BLUE) {
                background_color = YELLOW;
            }
            else if (background_color == YELLOW) {
                background_color = GREEN;
            }
            else if (background_color == GREEN) {
                background_color = BLUE;
            }
        }

        // If the button is pressed restart the timer
        button = gpio_input_bit_get(GPIOA, GPIO_PIN_8);

        if (button) {
            start = timer_start();
            triggered = 0;
            background_color = BLUE;
        }

        // display time till alarm goes off
        display_int(8 * 16, 16, timer_diff);
        display_time(8 * 12, 24, TIMER_DURATION - timer_diff);

        delay_1ms(100);
    }

    return 0;
}
