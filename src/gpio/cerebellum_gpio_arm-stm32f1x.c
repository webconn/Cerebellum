/**
 * @file src/gpio/cerebellum_gpio_arm-stm32f1x.c
 * @brief GPIO high-level operation implementation for ARM (STM32F1X)
 */

#include <lib/cerebellum/gpio.h>

void gpio_init(struct gpio_pin gpio, gpio_mode_t mode)
{
        switch (mode) {
                case GPIO_MODE_IN:
                        *(gpio.port - 1) &= ~(1<<(gpio.pin));
                        *(gpio.port) &= ~(1<<(gpio.pin)); /* disable pullup */
                        break;
                case GPIO_MODE_IN_PU:
                        *(gpio.port - 1) &= ~(1<<(gpio.pin));
                        *(gpio.port) |= (1<<(gpio.pin)); /* enable pullup */
                        break;
                case GPIO_MODE_OUT:
                        *(gpio.port - 1) |= (1<<(gpio.pin));
                        break;
                        /** @todo Insert assertion_failed macros */
        }
}

void gpio_write(struct gpio_pin gpio, gpio_state_t state)
{
        if (state) /* state == GPIO_HIGH) */
                *(gpio.port) |= (1<<(gpio.pin));
        else 
                *(gpio.port) &= ~(1<<(gpio.pin));
}

gpio_state_t gpio_read(struct gpio_pin gpio)
{
        return (*(gpio.port - 2) & (1<<(gpio.pin))) != 0;
}

void gpio_toggle(struct gpio_pin gpio)
{
        *(gpio.port) ^= (1<<(gpio.pin));
}
