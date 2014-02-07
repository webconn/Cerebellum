#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_HELPERS_AVR_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_HELPERS_AVR_GPIO_H

/**
 * Helpful macroses to initialize, read and write values to GPIO
 * Part of Cerebellum library
 * http://dimrobotics.com/cerebellum
 * http://github.com/DIMRobotics/Cerebellum
 */

#include <lib/cerebellum/helpers/basic.h>

#define GPIO_INIT_OUT(port, pin) do { *(&port + 1) |= (1 << pin); } while (0)
#define GPIO_INIT_IN(port, pin) do { *(&port + 1) &= ~(1 << pin); } while (0)
#define GPIO_INIT_IN_PULLUP(port, pin) GPIO_INIT_IN(port, pin); GPIO_WRITE_HIGH(port, pin)

#define GPIO_READ(port, pin) (*(&port + 2) & (1 << pin))
#define GPIO_WRITE_HIGH(port, pin) do { port |= (1 << pin); } while (0)
#define GPIO_WRITE_LOW(port, pin) do { port &= ~(1 << pin); } while (0)

#endif
