/**
 * General motors options and typedefs
 * for Cerebellum Library
 */

#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_MOTORS_GENERIC_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_MOTORS_GENERIC_H

/**
 * Direction typedef
 * Basically, each motor could rotate
 * forward, backward or stay stopped.
 * Also, there is an unlocked state.
 *
 * If motor couldn't be unlocked, this option
 * must be parsed like STOP.
 */

#include <stdint.h>

typedef enum {
        FORWARD = 0,
        BACKWARD = 1,
        STOP = 2,
        UNLOCK = 3
} motor_dir_t;

/**
 * Motor ID typedef
 * Simply the best-perfomance uint type
 * for machine
 */

#if defined(CONFIG_ARCH_AVR)
typedef uint8_t motor_t;
#else
typedef unsigned int motor_t;
#endif

/**
 * Motor speed typedef
 * It should be the best performance int type
 * Also, define top and bottom speed values
 *
 * These speed values could not be larger than +-32767.
 */

#if defined(CONFIG_ARCH_AVR)

#define CEREBELLUM_MAX_SPEED 127
#define CEREBELLUM_MIN_SPEED -127
typedef int16_t motor_val_t;

#else

#define CEREBELLUM_MAX_SPEED 32767
#define CEREBELLUM_MIN_SPEED -32767
typedef int motor_val_t;

#endif

typedef int32_t motor_path_t;
typedef int motor_speed_t;

#endif
