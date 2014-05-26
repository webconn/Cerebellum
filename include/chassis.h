#ifndef ANTARES_LIB_CEREBELLUM_CHASSIS_H
#define ANTARES_LIB_CEREBELLUM_CHASSIS_H

/**
 * @file include/chassis.h
 * @brief Chassis interface
 *
 * Chassis interface is a special set of function which implements
 * robot chassis control (movement commands)
 *
 * Interface is typical, but implementation is given by special libraries
 * such as Stepper or Motors
 */

#include <lib/cerebellum/motors_generic.h>

/**
 * @defgroup chassis_interface Chassis interface
 * @{
 */

void chassis_write(motor_speed_t left, motor_speed_t right);
void chassis_move(motor_speed_t left, motor_speed_t right, motor_speed_t acc, motor_speed_t acc_div, motor_path_t path);
void chassis_stop(void);
void chassis_pause(void);
void chassis_resume(void);
void chassis_setup_ebrake(motor_speed_t left, motor_speed_t right);

void chassis_interrupt(void); /* function to call in timer interrupt or task manager */

void chassis_reset(void);
uint8_t chassis_busy(void);
void chassis_wait(void);

/**
 * @}
 */

#endif
