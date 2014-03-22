/**
 * @file stepper/cerebellum_stepper.c
 * @brief Stepping motor driver interface
 */

#include <lib/cerebellum/stepper.h>
        
/* ACHTUNG! */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#ifdef CONFIG_LIB_CEREBELLUM_STEPPER_VALTABLE
#include "val_table.inc"
#endif

static volatile struct stepper_motors_s {
        int32_t path;
        int8_t dir;
        uint8_t state;
        uint16_t delay;
        uint16_t base_delay;
} steppers[CONFIG_LIB_CEREBELLUM_STEPPER_NUM];


/**
 * @brief Unlock (enable) driver
 *
 * Send enabling signal to ENABLE/ESTOP pin on driver
 */
void stepper_enable(void)
{
#ifdef CONFIG_LIB_CEREBELLUM_STEPPER_INV
        GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_ENABLE);
#else
        GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_ENABLE);
#endif
}

/**
 * @brief Lock (disable) driver
 *
 * Send disabling signal to ENABLE/ESTOP pin on driver
 */
void stepper_disable(void)
{
#ifdef CONFIG_LIB_CEREBELLUM_STEPPER_INV
        GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_ENABLE);
#else
        GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_ENABLE);
#endif
}

/**
 * @brief Set direction of motor rotation
 *
 * Set high or low level on DIR pin of driver channel.
 * 
 * In normal mode, HIGH value on pin is for forward direction, LOW for backward.
 * To inverse it, look menuconfig.
 *
 * @param[in] motor Index of motor
 * @param[in] dir Direction (FORWARD or BACKWARD)
 */
void stepper_set_dir(motor_t motor, motor_dir_t dir)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return; /* TODO: assert_failed() here */
        
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 1
        if (motor == 0)
                #ifdef CONFIG_LIB_CEREBELLUM_STEPPER_DIR_INV_1
                dir == FORWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_1) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_1);
                #else
                dir == BACKWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_1) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_1);
                #endif
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 2
        else if (motor == 1) 
                #ifdef CONFIG_LIB_CEREBELLUM_STEPPER_DIR_INV_2
                dir == FORWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_2) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_2);
                #else
                dir == BACKWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_2) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_2);
                #endif
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 3
        else if (motor == 2) 
                #ifdef CONFIG_LIB_CEREBELLUM_STEPPER_DIR_INV_3
                dir == FORWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_3) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_3);
                #else
                dir == BACKWARD ? GPIO_WRITE_LOW(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_3) : GPIO_WRITE_HIGH(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_3);
                #endif
#endif
        
        steppers[motor].dir = dir == FORWARD ? 1 : -1;
}

/**
 * @brief Set delay of motor step (in microseconds)
 *
 * Configure "software timer" of motor to wait for required number of microseconds
 * before toggle STEP pin of driver channel.
 * 
 * @param[in] motor Index of motor
 * @param[in] delay Step delay (in microseconds)
 */
void stepper_set_delay(motor_t motor, uint16_t delay)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return; /* TODO: assert_failed() here */

        if (delay != 0 && delay < 16)
                delay = 16;
        
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) /* TODO: replace with ANTARES_ATOMIC */
        {
                steppers[motor].base_delay = delay / 16; /* this division is for conversion to microseconds */
        }
}

/**
 * @brief Set speed (in rotates per minute) value of motor
 *
 * This function uses motor resolution value to calculate rpm value.
 *
 * Formula: delay = 60000000 / (val * resolution)
 *
 * As you can see, it uses large numbers and division, so avoid using of this on slow hardware.
 * 
 * @param[in] motor Index of motor
 * @param[in] val Speed value (in rotates per minute)
 */
void stepper_set_rpm(motor_t motor, motor_speed_t val)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return; /* TODO: assert_failed() here */

        
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 1
        if (motor == 0)
                val *= CONFIG_LIB_CEREBELLUM_STEPPER_RESOL_1;
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 2
        else if (motor == 1) 
                val *= CONFIG_LIB_CEREBELLUM_STEPPER_RESOL_2;
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 3
        else if (motor == 2) 
                val *= CONFIG_LIB_CEREBELLUM_STEPPER_RESOL_3;
#endif

        if (val != 0)
                val = 60000000 / val;
        stepper_set_delay(motor, val);
}

/**
 * @brief Set speed value of motor (from delay table)
 *
 * Set relative speed value (from 0 to 100 in this case) for 
 * motor. Delay value for this index going from values table.
 * 
 * @param[in] motor Index of motor
 * @param[in] speed Speed value (index in values table)
 */
void stepper_set_speed(motor_t motor, motor_val_t speed)
{
        if (speed < 0)
                speed = -speed;
        if (speed > 100)
                speed = 100;

        stepper_set_delay(motor, val_table[speed]);
}

/**
 * @brief Set signed value of speed (including direction)
 *
 * The same as getting sign of value, setting direction and 
 * writing speed (using stepper_set_speed() ).
 *
 * @param[in] motor Index of motor
 * @param[in] value Signed speed value for motor (index in values table)
 */
void stepper_write(motor_t motor, motor_val_t value)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return; /* TODO: assert_failed() here */
        
        if (value < 0) {
                value = -value;
                stepper_set_dir(motor, BACKWARD);
        } else {
                stepper_set_dir(motor, FORWARD);
        }
        
#ifdef CONFIG_LIB_CEREBELLUM_STEPPER_VALTABLE
        stepper_set_speed(motor, value);
#else
        stepper_set_real_speed(motor, (uint16_t) value << 6);
#endif
}

/**
 * @brief Get relative path made by stepping motor
 *
 * Path value accords to motor direction, so it is signed; decrements
 * if motor moves backward and increments if motor moves forward.
 *
 * @param[in] motor Index of motor
 * @return Path value
 */
motor_path_t stepper_get_path(motor_t motor)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return 0; /* TODO: assert_failed() here */
        
        int32_t val;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
                val = steppers[motor].path;
        }
        
        return val;
}

/**
 * @brief Reset relative path of motor (set it to 0)
 *
 * Set current point as "zero"
 *
 * @param[in] motor Index of motor
 */
void stepper_reset_path(motor_t motor)
{
        if (motor >= CONFIG_LIB_CEREBELLUM_STEPPER_NUM)
                return; /* TODO: assert_failed() here */
        
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
                steppers[motor].path = 0;
        }
}

static inline void toggle(motor_t motor)
{
        if (steppers[motor].base_delay) {
                #if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 1
                        if (motor == 0)
                                GPIO_TOGGLE(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_1);
                #endif
                #if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 2
                        else if (motor == 1) 
                                GPIO_TOGGLE(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_2);
                #endif
                #if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 3
                        else if (motor == 2) 
                                GPIO_TOGGLE(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_3);
                #endif
        
                steppers[motor].path += steppers[motor].dir;
        }
}

/**
 * @section "System functions"
 * @brief Driver timer interrupt handler
 *
 * Run this function in your system timer interrupt handler to set
 * stepping motor driver work.
 */
void stepper_interrupt(void)
{
        for (uint8_t i=0; i<CONFIG_LIB_CEREBELLUM_STEPPER_NUM; i++) {
                if (steppers[i].delay != 0) {
                        steppers[i].delay--;
                } else {
                        toggle(i);
                        steppers[i].delay = steppers[i].base_delay;
                }
        }
}

