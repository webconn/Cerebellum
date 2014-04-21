#ifndef ANTARES_LIB_CEREBELLUM_CHASSIS_H
#define ANTARES_LIB_CEREBELLUM_CHASSIS_H

#include <lib/cerebellum/motors_generic.h>

void chassis_write(motor_speed_t left, motor_speed_t right);
void chassis_move(motor_speed_t left, motor_speed_t right, motor_speed_t acc, motor_speed_t acc_div, motor_path_t path);
void chassis_stop(void);
void chassis_pause(void);
void chassis_resume(void);

void chassis_interrupt(void); /* function to call in timer interrupt or task manager */

void chassis_reset(void);
uint8_t chassis_busy(void);
void chassis_wait(void);

#endif
