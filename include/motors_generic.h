/**
 * @file include/motors_generic.h
 * @brief General motors options and typedefs
 */

#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_MOTORS_GENERIC_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_MOTORS_GENERIC_H

#include <stdint.h>

/**
 * @brief Direction typedef
 * 
 * Basically, each motor could rotate forward, backward or stay stopped.
 * Also, there is an unlocked state. If motor couldn't be unlocked, this option
 * need to be parsed like STOP.
 */

typedef enum {
        FORWARD = 0,
        BACKWARD = 1,
        STOP = 2,
        UNLOCK = 3
} motor_dir_t;

/**
 * @brief Motor ID typedef
 * 
 * Usually just the best-perfomance unsigned integer type for arch. Must be used
 * to enumerate motors in multi-motor systems.
 */
#if defined(CONFIG_ARCH_AVR)
typedef uint8_t motor_t;
#else
typedef unsigned int motor_t;
#endif

/**
 * @typedef motor_val_t
 * @brief Motor value typedef
 * 
 * This typedef stores local <b>hardware</b> speed value (ex. PWM value)
 * It should be the best performance signed int type.
 * These speed values could not be absolutely larger than 32767.
 */

#if defined(CONFIG_ARCH_AVR)

#define CEREBELLUM_MAX_SPEED 127
#define CEREBELLUM_MIN_SPEED -127
typedef int8_t motor_val_t;

#else

#define CEREBELLUM_MAX_SPEED 32767
#define CEREBELLUM_MIN_SPEED -32767
typedef int motor_val_t;

#endif

/**
 * @brief Motor path value typedef
 *
 * Path is calculated in local units (ex. ticks of encoder, steps etc.).
 * To convert it to real units (mm or something else), use special conversion macroses.
 */
typedef int32_t motor_path_t;

/**
 * @brief Motor speed value typedef
 *
 * Speed value is stored in local units (ex. ticks of encoder, steps etc.).
 * To convert it to real units (mm or something else), use special conversion macroses.
 */
typedef int motor_speed_t;

#endif
