#include <arch/antares.h> 
#include <util/delay.h>  
#include <lib/cerebellum/gpio.h>

static struct gpio_pin button_gpio;
static struct gpio_pin led_gpio = GPIO_DESCR(GPD6); /* initialize descriptor on declaration */

/* low-level init; runs once before interrupts are globally enabled */
ANTARES_INIT_LOW(io_init) 
{
        GPIO_INIT_DESCR(button_gpio, GPD5); /* another way to write descriptor; work in any place */
        gpio_init(led_gpio, GPIO_MODE_OUT); /* init led pin to be output */
        gpio_init(button_gpio, GPIO_MODE_IN_PU); /* init button to be input with pullup */
}

/* Application; this function will run in forever loop */
ANTARES_APP(button) 
{
        gpio_write(led_gpio, !gpio_read(button_gpio));
}
