#ifndef LIB_CEREBELLUM_ARCH_AVR_GENERIC_H
#define LIB_CEREBELLUM_ARCH_AVR_GENERIC_H

/**
 * @file include/arch/avr/generic.h
 * @brief Generic arch-specific configuration for AVR
 */

#include <stdint.h>

/**
 * @brief The most comfortable signed int type
 * For AVR, this type is 8-bit signed integer
 */
typedef int8_t arch_int_t;

/**
 * @brief The most comfortable unsigned int type
 * For AVR, this type is 8-bit integer
 */
typedef uint8_t arch_uint_t;

#endif
