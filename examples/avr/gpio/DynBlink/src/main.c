#include <arch/antares.h> /* for Antares startup macros */
#include <util/delay.h>  
#include <lib/cerebellum/gpio.h> /* for Cerebellum GPIO HAL */

/* LED pin description structure (PD6) */
static struct gpio_pin led_pin = {
        .port = GPIO_D,
        .pin = 6
};


/* Low init; run once before interrupts are globally enabled */
ANTARES_INIT_LOW(io_init) 
{
        gpio_init(led_pin, GPIO_MODE_OUT);
}


/* Application; this function will run in forever loop */
ANTARES_APP(blink) 
{
        /* Write HIGH value to LED_PIN -> turn on */
        gpio_write(led_pin, GPIO_HIGH);
        /* wait a bit */
        _delay_ms(300);
        /* Write LOW value to LED_PIN -> turn off */
        gpio_write(led_pin, GPIO_LOW);
        /* wait a bit */
        _delay_ms(300);
}

