/**
 * Cerebellum Library GPIO expansion
 * helpers for AVR
 */

#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H

#include <avr/io.h>

/**
 * Include list of GPIO expansion
 */
#include <lib/cerebellum/arch/avr/gpio_expansion.h>

/**
 * Raw macroses
 */

#define GPIO_INIT_OUT_RAW(port, ddr, pin, num) do { ddr |= (1<<num); } while (0)
#define GPIO_INIT_IN_RAW(port, ddr, pin, num) do { ddr &= ~(1<<num); port &= ~(1<<num); } while (0)
#define GPIO_INIT_IN_PU_RAW(port, ddr, pin, num) do { ddr &= ~(1<<num); port |= (1<<num); } while (0)

#define GPIO_READ_RAW(port, ddr, pin, num) (pin & (1<<num))
#define GPIO_WRITE_HIGH_RAW(port, ddr, pin, num) (port |= (1<<num))
#define GPIO_WRITE_LOW_RAW(port, ddr, pin, num) (port &= ~(1<<num))

/**
 * Short macroses
 */

#define GPIO_INIT_OUT(gpio) GPIO_INIT_OUT_RAW(gpio)
#define GPIO_INIT_IN(gpio) GPIO_INIT_IN_RAW(gpio)
#define GPIO_INIT_IN_PU(gpio) GPIO_INIT_IN_PU_RAW(gpio)
#define GPIO_READ(gpio) GPIO_READ_RAW(gpio)
#define GPIO_WRITE_HIGH(gpio) GPIO_WRITE_HIGH_RAW(gpio)
#define GPIO_WRITE_LOW(gpio) GPIO_WRITE_LOW_RAW(gpio)

#endif
