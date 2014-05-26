#include <arch/antares.h> /* for Antares startup macros */
#include <util/delay.h>  
#include <lib/cerebellum/gpio.h> /* for Cerebellum GPIO HAL macros */

/* We are using PD6 as LED pin */
#define LED_PIN GPD6

/* Low init; run once before interrupts are globally enabled */
ANTARES_INIT_LOW(io_init) 
{       
        /* Init LED_PIN to be output */
        GPIO_INIT_OUT(LED_PIN);
}

/* Application; this function will run in forever loop */
ANTARES_APP(blink) 
{
        /* Write HIGH value to LED_PIN -> turn on */
        GPIO_WRITE_HIGH(LED_PIN);
        /* wait a bit */
        _delay_ms(300);
        /* Write LOW value to LED_PIN -> turn off */
        GPIO_WRITE_LOW(LED_PIN);
        /* wait a bit */
        _delay_ms(300);
}

