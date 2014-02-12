#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H

#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

extern volatile uint8_t *_GPIO_AVR_ADDR[8];

typedef enum {
        GPIO_MODE_OUT,
        GPIO_MODE_IN,
        GPIO_MODE_IN_PULLUP
} gpio_mode_t;

#define GPIO_PIN(gpio) ((gpio) & 0x0F)
#define GPIO_PORT(gpio) (*((volatile uint8_t *) _GPIO_AVR_ADDR[((gpio) >> 4)]))

#define GPIO_READ(gpio) (*(&GPIO_PORT(gpio) - 2) & (1 << GPIO_PIN(gpio)))
#define GPIO_WRITE_HIGH(gpio) do { GPIO_PORT(gpio) |= (1 << GPIO_PIN(gpio)); } while (0)
#define GPIO_WRITE_LOW(gpio) do { GPIO_PORT(gpio) &= ~(1 << GPIO_PIN(gpio)); } while (0)

#define GPIO_INIT_OUT(gpio) do { *(&GPIO_PORT(gpio) - 1) |= (1 << GPIO_PIN(gpio)); } while (0)
#define GPIO_INIT_IN(gpio) do { *(&GPIO_PORT(gpio) - 1) &= ~(1 << GPIO_PIN(gpio)); } while (0)
#define GPIO_INIT_IN_PULLUP(gpio) do { GPIO_INIT_IN(gpio); GPIO_WRITE_HIGH(gpio); } while (0)

#endif
