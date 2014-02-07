#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_HELPERS_ARM_STM32F10X_H_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_HELPERS_ARM_STM32F10X_H_GPIO_H

#include <lib/cerebellum/helpers/basic.h>

#define GPIO_INIT_STRUCT() static GPIO_InitTypeDef gpio_init;

#define GPIO_INIT_OUT_PP(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_Out_PP; \
                gpio_init.GPIO_Speed = GPIO_Speed_50MHz; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_INIT_OUT_OD(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_Out_OD; \
                gpio_init.GPIO_Speed = GPIO_Speed_50MHz; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_INIT_AF_PP(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_AF_PP; \
                gpio_init.GPIO_Speed = GPIO_Speed_50MHz; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_INIT_AF_OD(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_AF_OD; \
                gpio_init.GPIO_Speed = GPIO_Speed_50MHz; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_INIT_IN(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)


#define GPIO_INIT_IN_PULLUP(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_IPU; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_INIT_IN_PULLDOWN(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_IPD; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)


#define GPIO_INIT_AIN(port, pin) \
        do { \
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_##port, ENABLE); \
                gpio_init.GPIO_Mode = GPIO_Mode_AIN; \
                gpio_init.GPIO_Pin = (1 << pin); \
                GPIO_Init(&gpio_init); \
        } while (0)

#define GPIO_READ(port, pin) GPIO_ReadInputDataBit(port, (1<<pin))
#define GPIO_WRITE_HIGH(port, pin) GPIO_SetBits(port, (1<<pin))
#define GPIO_WRITE_LOW(port, pin) GPIO_ResetBits(port, (1<<pin))

#endif
