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

#define GPIO_DESCR_RAW(PORT, DDR, PIN, NUM) ((struct gpio_pin) { .port = &(PORT), .pin = (NUM) })
#define GPIO_INIT_DESCR_RAW(descr, PORT, DDR, PIN, NUM) do { descr.port = &(PORT); descr.pin = (NUM); } while (0)

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
/**
 * Get GPIO descriptor from macro
 * @param GPIO GPIO pin descrtipion macro (GPxy)
 */
#define GPIO_DESCR(gpio) GPIO_DESCR_RAW(gpio)
/**
 * Fill GPIO descriptor structure with given GPIO data
 * @param descr Name of descriptor structure (already declared)
 * @param GPIO GPIO pin description macro (GPxy)
 */
#define GPIO_INIT_DESCR(descr, gpio) GPIO_INIT_DESCR_RAW(descr, gpio)

#ifdef PORTA
/** reference to PORTA, PINA, DDRA */
#define GPIO_A &PORTA
#endif
#ifdef PORTB
/** reference to PORTB, PINB, DDRB */
#define GPIO_B &PORTB
#endif
#ifdef PORTC
/** reference to PORTC, PINC, DDRC */
#define GPIO_C &PORTC
#endif
#ifdef PORTD
/** reference to PORTD, PIND, DDRD */
#define GPIO_D &PORTD
#endif
#ifdef PORTE
/** reference to PORTE, PINE, DDRE */
#define GPIO_E &PORTE
#endif
#ifdef PORTF
/** reference to PORTF, PINF, DDRF */
#define GPIO_F &PORTF
#endif
#ifdef PORTG
/** reference to PORTG, PING, DDRG */
#define GPIO_G &PORTG
#endif
#ifdef PORTH
/** reference to PORTH, PINH, DDRH */
#define GPIO_H &PORTH
#endif


/* Arch-specific typedefs (for performance) */

/**
 * @brief GPIO port typedef
 *
 * Value which is given by macros GPIO_x (GPIO_A, GPIO_B, ...)
 * 
 * In fact, these values are pointers to PORTx register (PIN and DDR calculated with offset)
 */
typedef volatile uint8_t *gpio_port_t;


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
