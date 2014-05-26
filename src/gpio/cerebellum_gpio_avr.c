/**
 * @file src/gpio/cerebellum_gpio_avr.c
 * @brief GPIO high-level operation implementation for AVR
 */

#include <avr/pgmspace.h>
#include <lib/cerebellum/gpio.h>

#ifdef CONFIG_LIB_CEREBELLUM_GPIO_PROGMEM
static volatile uint8_t *ports[] PROGMEM = {
#else
static volatile uint8_t *ports[] = {
#endif
        
        #ifdef PINA
                [GPIO_A] = &PINA,
        #endif
        #ifdef PINB
                [GPIO_B] = &PINB,
        #endif
        #ifdef PINC
                [GPIO_C] = &PINC,
        #endif
        #ifdef PIND
                [GPIO_D] = &PIND,
        #endif
        #ifdef PINE
                [GPIO_E] = &PINE,
        #endif
        #ifdef PINF
                [GPIO_F] = &PINF,
        #endif
        #ifdef PING
                [GPIO_G] = &PING,
        #endif
        #ifdef PINH
                [GPIO_H] = &PINH,
        #endif
};

void gpio_init(const struct gpio_pin *gpio, gpio_mode_t mode)
{
        switch (mode) {
                case GPIO_MODE_IN:
                        *(ports[gpio->port] + 1) &= ~(1<<(gpio->pin));
                        *(ports[gpio->port]) &= ~(1<<(gpio->pin)); /* disable pullup */
                        break;
                case GPIO_MODE_IN_PU:
                        *(ports[gpio->port] + 1) &= ~(1<<(gpio->pin));
                        *(ports[gpio->port]) |= (1<<(gpio->pin)); /* enable pullup */
                        break;
                case GPIO_MODE_OUT:
                        *(ports[gpio->port] + 1) |= (1<<(gpio->pin));
                        break;
                        /** @todo Insert assertion_failed macros */
        }
}

void gpio_write(const struct gpio_pin *gpio, gpio_state_t state)
{
        if (state) /* state == GPIO_HIGH) */
                *(ports[gpio->port]) |= (1<<(gpio->pin));
        else 
                *(ports[gpio->port]) &= ~(1<<(gpio->pin));
}

gpio_state_t gpio_read(const struct gpio_pin *gpio)
{
        return (*(ports[gpio->port] + 2) & (1<<(gpio->pin))) != 0;
}

void gpio_toggle(const struct gpio_pin *gpio)
{
        *(ports[gpio->port]) ^= (1<<(gpio->pin));
}
