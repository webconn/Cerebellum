#ifndef ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_F1X_GPIO_H
#define ANTARES_LIB_CEREBELLUM_ARCH_ARM_STM32_F1X_GPIO_H

/**
 * @file include/arch/arm-stm32/f1x/gpio.h
 * @brief GPIO HAL for ARM arch (STM32F1X)
 */

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "../generic.h"

/**
 * @defgroup hal_gpio_arm_stm32f1x GPIO ARM implementation (STM32F10x)
 * @ingroup hal_gpio
 * @brief ARM (STM32F10x chips) hardware support layer for GPIO HAL
 */

/**
 * @addtogroup hal_gpio_arm_stm32f1x
 * @{
 */


/* Arch-specific typedefs (for performance) */

/**
 * @brief GPIO port typedef
 *
 * Value which is given by macros GPIO_x (GPIO_A, GPIO_B, ...)
 * 
 * In fact, these values are pointers to GPIOx register blocks
 */
typedef GPIO_TypeDef *gpio_port_t;

/**
 * @brief GPIO modes enum
 *
 * List of supported GPIO modes in AVR
 */
typedef enum {
        /** Output (push-pull) */
        GPIO_MODE_OUT = GPIO_Mode_Out_PP,
        GPIO_MODE_OUT_PP = GPIO_Mode_Out_PP,
        /** Output (open drain) */
        GPIO_MODE_OUT_OD = GPIO_Mode_Out_OD,
        /** Input (Hi-Z state) */
        GPIO_MODE_IN = GPIO_Mode_IN_FLOATING,
        /** Input with Pull-up */
        GPIO_MODE_IN_PU = GPIO_Mode_IPU,
        /** Input with Pull-down */
        GPIO_MODE_IN_PD = GPIO_Mode_IPD
} gpio_mode_t;

/**
 * @brief GPIO pin description structure
 * Used in dynamical GPIO abstraction
 */
struct gpio_pin {
        gpio_port_t port;
        arch_uint_t pin;
};

/* Raw macros */
#define GPIO_INIT_OUT_PP_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_Out_PP, .GPIO_Speed = (speed), .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_OUT_OD_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_Out_OD, .GPIO_Speed = (speed), .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_OUT__AFPP_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_AF_PP, .GPIO_Speed = (speed), .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_OUT_AFOD_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_AF_OD, .GPIO_Speed = (speed), .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_IN_HIZ_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_IN_FLOATING, .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_IN_PU_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_IPU, .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_IN_PD_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_IPD, .GPIO_Pin = (1<<(num)) });  } while (0)
#define GPIO_INIT_AIN_RAW(port, rcc, speed, num) do { RCC_APB2PeriphClockCmd((rcc), ENABLE); GPIO_Init(port, (GPIO_InitTypeDef *) &{ .GPIO_Mode = GPIO_Mode_AIN, .GPIO_Pin = (1<<(num)) });  } while (0)

#define GPIO_READ_RAW(port, rcc, speed, num) (GPIO_ReadInputDataBit(port, (1<<(num))))
#define GPIO_WRITE_HIGH_RAW(port, rcc, speed, num) do { (port)->BSRR |= (1<<num); } while (0)
#define GPIO_WRITE_LOW_RAW(port, rcc, speed, num) do { (port)->BRR |= (1<<num); } while (0)
#define GPIO_TOGGLE_RAW(port, rcc, speed, num) do { (port)->ODR ^= (1<<(num)); } while (0)

#define GPIO_DESCR_RAW(PORT, rcc, speed, NUM) { .port = (PORT), .pin = (NUM) }

/* Short macros */


/**
 * Configure selected GPIO pin as push-pull output 
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_OUT(gpio) GPIO_INIT_OUT_PP_RAW(gpio)
#define GPIO_INIT_OUT_PP(gpio) GPIO_INIT_OUT_PP_RAW(gpio)
/**
 * Configure selected pin as open-drain output
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_OUT_OD(gpio) GPIO_INIT_OUT_OD_RAW(gpio)
/** 
 * @brief Configure selected GPIO pin as input
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_IN(gpio) GPIO_INIT_IN_HIZ_RAW(gpio)
#define GPIO_INIT_IN_HIZ(gpio) GPIO_INIT_IN_HIZ_RAW(gpio)
/** 
 * Configure selected GPIO pin as input with pull-up
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_IN_PU(gpio) GPIO_INIT_IN_PU_RAW(gpio)
/**
 * Configure selected GPIO pin as input with pull-down
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_IN_PD(gpio) GPIO_INIT_IN_PD_RAW(gpio)
/**
 * Configure selected GPIO pin as analog input
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_AIN(gpio) GPIO_INIT_AIN_RAW(gpio)
/** 
 * Read value from GPIO pin
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_READ(gpio) GPIO_READ_RAW(gpio)
/**
 * Write 1 (HIGH) value into GPIO pin
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_WRITE_HIGH(gpio) GPIO_WRITE_HIGH_RAW(gpio)
/** 
 * Write 0 (LOW) value into GPIO pin
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_WRITE_LOW(gpio) GPIO_WRITE_LOW_RAW(gpio)
/** 
 * Toggle GPIO pin (change value from 0 to 1 or from 1 to 0)
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_TOGGLE(gpio) GPIO_TOGGLE_RAW(gpio)
/**
 * Get GPIO descriptor from macro
 * @param GPIO GPIO pin descrtipion macro (GPxy)
 */
#define GPIO_DESCR(gpio) GPIO_DESCR_RAW(gpio)
/**
 * Get GPIO descriptior from macro as constant
 * (ex. to use as function argument)
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_STR(gpio) ((struct gpio_pin) GPIO_DESCR_RAW(gpio))
/**
 * Fill GPIO descriptor structure with given GPIO data
 * @param descr Name of descriptor structure (already declared)
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_DESCR(descr, gpio) GPIO_INIT_DESCR_RAW(descr, gpio)

#ifdef GPIOA
/** reference to GPIOA */
#define GPIO_A GPIOA
#endif
#ifdef GPIOB
/** reference to GPIOB */
#define GPIO_B GPIOB
#endif
#ifdef GPIOC
/** reference to GPIOC */
#define GPIO_C GPIOC
#endif
#ifdef GPIOD
/** reference to GPIOD */
#define GPIO_D GPIOD
#endif
#ifdef GPIOE
/** reference to GPIOE */
#define GPIO_E GPIOE
#endif
#ifdef GPIOF
/** reference to GPIOF */
#define GPIO_F GPIOF
#endif
#ifdef GPIOG
/** reference to GPIOG */
#define GPIO_G GPIOG
#endif
#ifdef GPIOH
/** reference to GPIOH */
#define GPIO_H GPIOH
#endif

/**
 * @}
 */


#endif
