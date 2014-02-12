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

typedef uint8_t gpio_t;

typedef enum {
        GPIO_HIGH = 1,
        GPIO_LOW = 0
} gpio_state_t;

void gpio_init(gpio_t gpio, gpio_mode_t mode);
void gpio_write(gpio_t gpio, gpio_state_t state);
gpio_state_t gpio_read(gpio_t gpio);

#define GPA0 0x00
#define GPA1 0x01
#define GPA2 0x02
#define GPA3 0x03
#define GPA4 0x04
#define GPA5 0x05
#define GPA6 0x06
#define GPA7 0x07
#define GPA8 0x08
#define GPA9 0x09
#define GPA10 0x0a
#define GPA11 0x0b
#define GPA12 0x0c
#define GPA13 0x0d
#define GPA14 0x0e
#define GPA15 0x0f

#define GPB0 0x10
#define GPB1 0x11
#define GPB2 0x12
#define GPB3 0x13
#define GPB4 0x14
#define GPB5 0x15
#define GPB6 0x16
#define GPB7 0x17
#define GPB8 0x18
#define GPB9 0x19
#define GPB10 0x1a
#define GPB11 0x1b
#define GPB12 0x1c
#define GPB13 0x1d
#define GPB14 0x1e
#define GPB15 0x1f

#define GPC0 0x20
#define GPC1 0x21
#define GPC2 0x22
#define GPC3 0x23
#define GPC4 0x24
#define GPC5 0x25
#define GPC6 0x26
#define GPC7 0x27
#define GPC8 0x28
#define GPC9 0x29
#define GPC10 0x2a
#define GPC11 0x2b
#define GPC12 0x2c
#define GPC13 0x2d
#define GPC14 0x2e
#define GPC15 0x2f

#define GPD0 0x30
#define GPD1 0x31
#define GPD2 0x32
#define GPD3 0x33
#define GPD4 0x34
#define GPD5 0x35
#define GPD6 0x36
#define GPD7 0x37
#define GPD8 0x38
#define GPD9 0x39
#define GPD10 0x3a
#define GPD11 0x3b
#define GPD12 0x3c
#define GPD13 0x3d
#define GPD14 0x3e
#define GPD15 0x3f

#define GPE0 0x40
#define GPE1 0x41
#define GPE2 0x42
#define GPE3 0x43
#define GPE4 0x44
#define GPE5 0x45
#define GPE6 0x46
#define GPE7 0x47
#define GPE8 0x48
#define GPE9 0x49
#define GPE10 0x4a
#define GPE11 0x4b
#define GPE12 0x4c
#define GPE13 0x4d
#define GPE14 0x4e
#define GPE15 0x4f

#define GPF0 0x50
#define GPF1 0x51
#define GPF2 0x52
#define GPF3 0x53
#define GPF4 0x54
#define GPF5 0x55
#define GPF6 0x56
#define GPF7 0x57
#define GPF8 0x58
#define GPF9 0x59
#define GPF10 0x5a
#define GPF11 0x5b
#define GPF12 0x5c
#define GPF13 0x5d
#define GPF14 0x5e
#define GPF15 0x5f

#define GPG0 0x60
#define GPG1 0x61
#define GPG2 0x62
#define GPG3 0x63
#define GPG4 0x64
#define GPG5 0x65
#define GPG6 0x66
#define GPG7 0x67
#define GPG8 0x68
#define GPG9 0x69
#define GPG10 0x6a
#define GPG11 0x6b
#define GPG12 0x6c
#define GPG13 0x6d
#define GPG14 0x6e
#define GPG15 0x6f

#define GPH0 0x70
#define GPH1 0x71
#define GPH2 0x72
#define GPH3 0x73
#define GPH4 0x74
#define GPH5 0x75
#define GPH6 0x76
#define GPH7 0x77
#define GPH8 0x78
#define GPH9 0x79
#define GPH10 0x7a
#define GPH11 0x7b
#define GPH12 0x7c
#define GPH13 0x7d
#define GPH14 0x7e
#define GPH15 0x7f


#endif
