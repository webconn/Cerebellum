#ifndef ANTARES_LIB_CEREBELLUM_INCLUDE_ARCH_GENERIC_H
#define ANTARES_LIB_CEREBELLUM_INCLUDE_ARCH_GENERIC_H

/**
 * @file include/arch/generic.h
 * @brief Generic data for current architecture
 */

#ifdef CONFIG_ARCH_AVR
#include "avr/generic.h"
#endif

#ifdef CONFIG_MCU_STM32
#include "arm-stm32/generic.h"
#endif

#endif
