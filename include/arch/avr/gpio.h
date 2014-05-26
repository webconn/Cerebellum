#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_ARCH_AVR_GPIO_H

/**
 * @file include/arch/avr/gpio.h
 * @brief Arch-specific GPIO operations definitions for AVR
 */

/* Includes */
#include <avr/io.h>
/* Include list of GPIO expansion */
#include "gpio_expansion.h"

/**
 * @addtogroup hal_gpio
 * @{
 */

/* Raw macros */
#define GPIO_INIT_OUT_RAW(port, ddr, pin, num) do { ddr |= (1<<num); } while (0)
#define GPIO_INIT_IN_RAW(port, ddr, pin, num) do { ddr &= ~(1<<num); port &= ~(1<<num); } while (0)
#define GPIO_INIT_IN_PU_RAW(port, ddr, pin, num) do { ddr &= ~(1<<num); port |= (1<<num); } while (0)

#define GPIO_READ_RAW(port, ddr, pin, num) (pin & (1<<num))
#define GPIO_WRITE_HIGH_RAW(port, ddr, pin, num) (port |= (1<<num))
#define GPIO_WRITE_LOW_RAW(port, ddr, pin, num) (port &= ~(1<<num))

#ifdef __AVR_ATtiny2313__
#define GPIO_TOGGLE_RAW(port, ddr, pin, num) (pin |= (1<<num))
#else
#define GPIO_TOGGLE_RAW(port, ddr, pin, num) (port ^= (1<<num))
#endif

/* Short macros */

/**
 * @brief Configure selected GPIO pin as output 
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_OUT(gpio) GPIO_INIT_OUT_RAW(gpio)
/** 
 * @brief Configure selected GPIO pin as input
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_IN(gpio) GPIO_INIT_IN_RAW(gpio)
/** 
 * Configure selected GPIO pin as input with pullup
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_IN_PU(gpio) GPIO_INIT_IN_PU_RAW(gpio)
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

/* Arch-specific typedefs (for performance) */

/**
 * @brief GPIO port enum
 *
 * Index of GPIO port for usage in gpio_pin_t structure.
 */
typedef enum {
        /** reference to PORTA, PINA, DDRA */
        #ifdef PORTA
        GPIO_A,
        #endif
        /** reference to PORTB, PINB, DDRB */
        #ifdef PORTB
        GPIO_B,
        #endif
        /** reference to PORTC, PINC, DDRC */
        #ifdef PORTC
        GPIO_C,
        #endif
        /** reference to PORTD, PIND, DDRD */
        #ifdef PORTD
        GPIO_D = 3,
        #endif
        /** reference to PORTE, PINE, DDRE */
        #ifdef PORTE
        GPIO_E = 4,
        #endif
        /** reference to PORTF, PINF, DDRF */
        #ifdef PORTF
        GPIO_F = 5,
        #endif
        /** reference to PORTG, PING, DDRG */
        #ifdef PORTG
        GPIO_G = 6,
        #endif
        /** reference to PORTH, PINH, DDRH */
        #ifdef PORTH
        GPIO_H = 7
        #endif
} gpio_port_t;

/**
 * @brief GPIO modes enum
 *
 * List of supported GPIO modes in AVR
 */
typedef enum {
        /** Output (push-pull) */
        GPIO_MODE_OUT,
        /** Input (Hi-Z state) */
        GPIO_MODE_IN,
        /** Input with Pull-up */
        GPIO_MODE_IN_PU
} gpio_mode_t;

/**
 * @}
 */



#endif
