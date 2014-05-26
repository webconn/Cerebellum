#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_GPIO_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_GPIO_H

/**
 * @file include/gpio.h
 * @brief GPIO abstraction layer
 */

/**
 * @defgroup hal_gpio GPIO abstraction layer
 * 
 *
 * You can find something close to this in Arduino, where
 * devs replaces port-pin notation with numbers.
 *
 * In Cerebellum library, port-pin notation is not fully replaced,
 * but united in one structure to make system calls more
 * flexible.
 * 
 * GPIO HAL in Cerebellum library implements two ways to control GPIOs.
 *
 * <b>Tip</b>: These ways could be used together at same time.
 *
 * Way 1: Using Macros
 * ===================
 *
 * This way is the best for time-critical applications because all GPIO operations
 * will be parsed by C preprocessor and translated into "native" ASM instructions.
 * But the disadvantage of this way is that you can't store GPIO address in memory.
 *
 * Each GPIO in MCU has a name which consists of port letter and pin number.
 * Usually these names are written like PB3 (Port B pin 3). In Cerebellum library, these
 * names are given like GPB3 (GPxy, if you want). First letter G is added to avoid
 * conflicts with arch-specific C library (for example, in AVR-LIBC names Pxy are used
 * for pin names).
 *
 * To perform some action with GPIO pin, use short macros.
 *
 * Way 2: Using Structures
 * =======================
 *
 * This way is very flexible since each pin could be described as a couple of bytes in memory
 * and you can easily store it, but this way is not such fast as first. But it still has
 * its usecases (for easily configuring special libraries, to give GPIO as an argument into
 * function, etc.)
 *
 * @example examples/avr/gpio/Blink/src/main.c
 * @example examples/avr/gpio/DynBlink/src/main.c
 */

#include <stdint.h>

#ifdef CONFIG_ARCH_AVR
#include "arch/avr/gpio.h"
#endif

#include "arch/avr/generic.h"

/**
 * @addtogroup hal_gpio
 * @{
 */

/**
 * @brief GPIO pin description structure
 * Used in dynamical GPIO abstraction
 */
struct gpio_pin {
        /** GPIO port name */
        volatile uint8_t *port;
        /** GPIO pin number */
        arch_uint_t pin;
};

/**
 * @brief GPIO state typedef
 * Used to set up GPIO value
 */
typedef enum {
        /** Low value (set to GND) */
        GPIO_LOW = 0,
        /** High value (set to Vcc) */
        GPIO_HIGH
} gpio_state_t;

/* GPIO functions implementations */

/**
 * @brief Initialize GPIO pin to run in given mode
 *
 * @param [in] pin GPIO pin description structure
 * @param [in] mode GPIO operation mode
 *
 * @return Nothing to return
 */
void gpio_init(struct gpio_pin pin, gpio_mode_t mode);

/**
 * @brief Write given value into GPIO pin
 *
 * @param [in] pin GPIO pin description structure
 * @param [in] state Required GPIO state
 *
 * @return Nothing to return
 */
void gpio_write(struct gpio_pin pin, gpio_state_t state);

/**
 * @brief Read the state of GPIO pin
 *
 * @param [in] pin GPIO pin description structure
 *
 * @return Current voltage level on GPIO pin
 *
 * @retval GPIO_LOW if pin level is low (GND)
 * @retval GPIO_HIGH if pin level is high (Vcc)
 */
gpio_state_t gpio_read(struct gpio_pin pin);

/**
 * @brief Toggle GPIO pin
 * Change GPIO output level from HIGH to LOW and from LOW to HIGH
 *
 * @param [in] pin GPIO pin description structure
 *
 * @return Nothing to return
 */
void gpio_toggle(struct gpio_pin pin);

/**
 * @}
 */

#endif
