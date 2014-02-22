#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_GPIO_H

/**
 * GPIO abstraction layer
 *
 * You can find something close to this in Arduino, where
 * devs replaces port-pin notation with numbers.
 *
 * In Cerebellum library, port-pin notation is not fully replaced,
 * but united in one structure to make system calls more
 * flexible.
 */

#include <stdint.h>

#if defined(CONFIG_ARCH_AVR)
#include <lib/cerebellum/arch/avr/gpio.h>
#endif

#endif
