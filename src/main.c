#include "gd32vf103.h"
#include "display.h"
#include "timer.h"
#include "lcd/lcd.h"

#define TIMER_DURATION 90000

// initializes the spi port used for the lcd
void lcd_init() {
    spi_parameter_struct spi_init_struct;

    spi_init_struct.trans_mode = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_8;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    
    spi_init(SPI0, &spi_init_struct);
}

// draws a pixel on the lcd screen at point (x, y)
lcd_draw_pixel(int x, int y) {

}

// deinitializes the spi port used for the lcd
void lcd_deinit() {
    spi_i2s_deinit(SPI0);
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
