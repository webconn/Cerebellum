#ifndef LIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_H
#define LIB_CEREBELLUM_ARCH_ARM_STM32_GPIO_H

/**
 * @file include/arch/arm-stm32/gpio.h
 * @brief GPIO HAL for ARM architecure (STM32)
 */

#ifdef CONFIG_STM32F1X
#include "f1x/gpio.h"
#endif

#ifdef CONFIG_STM32F4X
#include "f4x/gpio.h"
#endif

#endif
