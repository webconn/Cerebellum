#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_STEPPER_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_STEPPER_H

#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/motors_generic.h>
#include <lib/cerebellum/board.h>

struct stepper_motors_s {
        int32_t path;
        int8_t dir;
        uint8_t state;
        uint16_t delay;
        uint16_t base_delay;
};

/**
 * Motor driving interface
 */

#ifndef CONFIG_ANTARES_STARTUP
void stepper_init(void);
#endif

void stepper_enable(void);
void stepper_disable(void);
void stepper_set_dir(motor_t motor, motor_dir_t dir);
void stepper_set_delay(motor_t motor, uint16_t delay);
void stepper_set_speed(motor_t motor, motor_val_t val);
void stepper_set_real_speed(motor_t motor, uint16_t speed);
void stepper_write(motor_t motor, motor_val_t val);

void stepper_interrupt(void); /* service function for timer interrupt */

/**
 * Motor feedback interface
 */
//motor_speed_t stepper_get_speed(motor_t motor);
motor_path_t stepper_get_path(motor_t motor);
void stepper_reset_path(motor_t motor);

#endif
