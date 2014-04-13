/**
 * @file stepper/cerebellum_stepper_chassis.c
 * @brief Standart chassis interface implementation for Stepper
 * @author Nikita 'webconn' Maslov
 */

#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <arch/antares.h>

#ifdef CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_SCHEME_CLASSIC

static volatile motor_val_t v_left, v_right;
static volatile motor_path_t p_left, p_right;

static volatile motor_path_t a_path;
static volatile motor_val_t a_left, a_right, a_div, r_left, r_right, min_left, min_right; /* r_left, r_right - required values; */
static volatile motor_val_t a_dval;
static volatile motor_path_t v_path, h_path, s_path;

typedef uint8_t (*interrupt_t)(void);
static volatile interrupt_t move_interrupt = NULL;

static enum {
        STATE_STOP = 0,
        STATE_START,
        STATE_PROCESS,
        STATE_BRAKE,
        STATE_PRESTOP,
        STATE_STATIC,
        STATE_PREINTERRUPT,
        STATE_INTERRUPT
} state; 

/**
 * @brief Write combined speed values to chassis (for each motor)
 *
 * Write signed speed values into each Stepper channel (using 
 * stepper_set_speed() function).
 * 
 * @param[in] left Value for left motor
 * @param[in] right Value for right motor
 */
void chassis_write(motor_speed_t left, motor_speed_t right)
{
        /* TODO: insert convertion from units to mm/s or equal */
        state = STATE_STATIC;
        v_left = left;
        v_right = right;
}

/**
 * @brief Setup smooth movement of chassis for defined path value
 *
 * Smooth movement is a movement with smoooth acceleration and braking.
 *
 * Acceleration value is set as a regular number (with separated denominator and divider). In
 * Chassis implementation, divider changes from 0 to maximum of motor_speed_t type. (0 means no divider, or
 * 1; look at this fact as real divider just adds 1 to its value).
 *
 * @param[in] left left Required left motor speed
 * @param[in] right Required right motor speed
 * @param[in] acc Denominator of acceleration value
 * @param[in] acc_div Divider of acceleraiotn value (from 0 to max of motor_speed_t)
 * @param[in] path Length of movement (signed! according to movement direction!)
 */
void chassis_move(motor_speed_t left, motor_speed_t right, motor_speed_t acc, motor_speed_t acc_div, motor_path_t path)
{
        /** @todo Fix path to be unsigned and calculate personal acceleration for left and right channels */
        chassis_reset();

        a_left = acc;
        a_right = acc;
        a_div = acc_div;
        a_dval = 0;

        if (left < 0)
                a_left = -a_left;

        if (right < 0)
                a_right = -a_right;

        r_left = left;
        r_right = right;

        min_left = 5;
        min_right = 5;

        v_path = path;
        h_path = path >> 1;
        s_path = 0;

        state = STATE_START;
}

void chassis_set_interrupt(uint8_t (*func)(void))
{
        move_interrupt = func;
}

uint8_t chassis_busy(void)
{
        register uint8_t st;
        ANTARES_ATOMIC_BLOCK()
        {
                st = state;
        }
        return st;
}

void chassis_wait(void)
{
        while (chassis_busy());
}

void chassis_reset(void)
{
        stepper_reset_path(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_LEFT);
        stepper_reset_path(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_RIGHT);
}

void chassis_stop(void)
{
        state = STATE_STOP;
}

#define abs(a) ((a) < 0 ? -(a) : (a))

static inline void process_move(void)
{
        p_left = stepper_get_path(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_LEFT);
        p_right = stepper_get_path(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_RIGHT);

        motor_path_t path = abs(p_left) + abs(p_right) / 2;

        if (state == STATE_START) { /* robot starts */
                a_dval++;
                if (a_dval == a_div) {
                        v_left += a_left;
                        v_right += a_right;
                        a_dval = 0;
                }

                if (abs(v_right) >= abs(r_right) || abs(v_left) >= abs(r_left)) {
                        state = STATE_PROCESS;
                        v_left = r_left;
                        v_right = r_right;
                        a_path = path - s_path; /* save acceleration path */
                }

                if (path >= h_path) {
                        state = STATE_BRAKE;
                        a_path = path - s_path;
                        a_dval = 0;
                }

                if (move_interrupt && move_interrupt()) 
                        state = STATE_PREINTERRUPT;

        } else if (state == STATE_PROCESS) { /* process */
                //v_left = r_left;
                //v_right = r_right;

                if (v_path - a_path <= path)
                        state = STATE_BRAKE;

                if (move_interrupt && move_interrupt())
                        state = STATE_PREINTERRUPT;

        } else if (state == STATE_BRAKE || state == STATE_PREINTERRUPT) {
                a_dval++;
                if (a_dval == a_div) {
                        v_left -= a_left;
                        v_right -= a_right;
                        a_dval = 0;
                }
                if (path >= v_path) { 
                        state = STATE_STOP;
                        v_left = 0;
                        v_right = 0;
                }
                if (abs(v_left) <= abs(min_left) || abs(v_right) <= abs(min_right)) {
                        if (state == STATE_BRAKE)
                                state = STATE_PRESTOP;
                        else /* if (state == STATE_PREINTERRUPT) */
                                state = STATE_INTERRUPT;
                }
        } else if (state == STATE_PRESTOP) {
                v_left = min_left;
                v_right = min_right;
                if (path >= v_path) {
                        state = STATE_STOP;
                        v_left = 0;
                        v_right = 0;
                }
        } else if (state == STATE_INTERRUPT) {
                v_left = 0;
                v_right = 0;

                if (move_interrupt && !move_interrupt()) {
                        h_path = (v_path - path) >> 1;
                        s_path = path;
                        if (h_path > 0) {
                                h_path += path;
                                state = STATE_START;
                        }
                        else
                                state = STATE_STOP;
                }
        }
}

void chassis_interrupt(void)
{
        /* Write values */
        if (!state) { /* chassis must stay at place */
                v_left = 0;
                v_right = 0;
        } else if (state != STATE_STATIC) {
                process_move();
        }
        
        stepper_write(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_LEFT, v_left);
        stepper_write(CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_RIGHT, v_right);
}


#endif
