#include "gd32vf103.h"
#include "display.h"
#include "timer.h"
#include "lcd.h"
#include "led.h"
#include "bgcol.h"
#include "lcd_char.h"
#include "starfield.inl"

#define TIMER_DURATION 90000

// Creating global frambuffer for lcd library
uint16_t g_fb[LCD_FRAMEBUFFER_PIXELS];

int main() {
    // LCD init
    led_init();
    lcd_init();

    // Init gpio for BOOT0 button that responds on PA8 after boot.
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);

    // Clear framebuffer
    for (int i = 0; i < LCD_FRAMEBUFFER_PIXELS; i++) {
        g_fb[i] = bgcol(i);
    }

    // Enable continuous framebuffer update
    lcd_fb_setaddr(g_fb);
    lcd_fb_enable();

    // State of BOOT0 button
    uint16_t button;

    // timer
    uint64_t start = timer_start();

    // State of timer
    uint16_t triggered = 1;
    int timer_diff = TIMER_DURATION;

    // Position of timer text
    int xbase = (LCD_WIDTH - 5 * CHAR_WIDTH) / 2, ybase = (LCD_HEIGHT - CHAR_HEIGHT) / 2;

    while(1) {
        // If the timer is not triggered do a countdown
        if (!triggered) {
            timer_diff = timer_diff_in_milliseconds(start);

            if (TIMER_DURATION - timer_diff <= 0) {
                triggered = 1;
                timer_diff = TIMER_DURATION;
            }
        }

        // If the button is pressed restart the timer
        button = gpio_input_bit_get(GPIOA, GPIO_PIN_8);

        if (button) {
            start = timer_start();
            triggered = 0;
        }

        // Update starfield from slmisc/gd32v-lcd
        for (int i=0; i < NUM_STARS; i++)
        {
            Star* s = &g_stars[i];
            if (s->p >= 0)
                g_fb[s->p] = bgcol(s->p);
            update_star(s, 10);
            if (s->p >= 0)
            {
                int g = (0x7fff - s->z) >> 9;
                if (g > 31) g = 31;
                int r = g>>1;
                g_fb[s->p] += (r << 11) | (g << 5) | r;
            }
        }

        // display time till alarm goes off
        display_time(xbase, ybase, TIMER_DURATION - timer_diff, g_fb);
    }

    return 0;
}
