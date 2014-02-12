#include <lib/cerebellum/gpio.h>

volatile uint8_t *_GPIO_AVR_ADDR[8] = {
        #if defined(PORTA)
                &PORTA,
        #else
                NULL,
        #endif

        #if defined(PORTB)
                &PORTB,
        #else
                NULL,
        #endif

        #if defined(PORTC)
                &PORTC,
        #else
                NULL,
        #endif

        #if defined(PORTD)
                &PORTD,
        #else
                NULL,
        #endif

        #if defined(PORTE)
                &PORTE,
        #else
                NULL,
        #endif

        #if defined(PORTF)
                &PORTF,
        #else
                NULL,
        #endif

        #if defined(PORTG)
                &PORTG,
        #else
                NULL,
        #endif

        #if defined(PORTH)
                &PORTH,
        #else
                NULL,
        #endif
};

void gpio_init(gpio_t gpio, gpio_mode_t mode)
{
        switch (mode) {
                case GPIO_MODE_OUT:
                        GPIO_INIT_OUT(gpio);
                        break;
                case GPIO_MODE_IN:
                        GPIO_INIT_IN(gpio);
                        break;
                case GPIO_MODE_IN_PULLUP:
                        GPIO_INIT_IN_PULLUP(gpio);
                        break;
                default:
                        break;
        }
}

void gpio_write(gpio_t gpio, gpio_state_t state)
{
        if (state == GPIO_HIGH)
                GPIO_WRITE_HIGH(gpio);
        else
                GPIO_WRITE_LOW(gpio);
}

gpio_state_t gpio_read(gpio_t gpio)
{
        return GPIO_READ(gpio);
}
