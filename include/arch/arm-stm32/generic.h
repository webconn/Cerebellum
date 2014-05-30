#ifndef ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_GENERIC_H
#define ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_GENERIC_H

/**
 * @file include/arch/arm-stm32/generic.h
 * @brief Generic arch-specific configuration for ARM-STM32
 */

#include <stdint.h>

/**
 * @brief The most comfortable signed int type
 * For ARM-STM32, this type is 32-bit signed integer
 */
typedef int32_t arch_int_t;

/**
 * @brief The most comfortable unsigned int type
 * For ARM-STM32, this type is 32-bit integer
 */
typedef uint32_t arch_uint_t;

#endif
