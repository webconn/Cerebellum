#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <arch/antares.h>

#ifdef CONFIG_LIB_CEREBELLUM_CHASSIS_STEPPER_SCHEME_CLASSIC

static volatile motor_val_t v_left, v_right;
static volatile motor_path_t p_left, p_right;

static volatile motor_path_t a_path;
static volatile motor_val_t a_left, a_right, a_div, r_left, r_right, min_left, min_right; /* r_left, r_right - required values; */
static volatile motor_val_t a_dval;
static volatile motor_path_t v_path, h_path;

static enum {
        STATE_STOP = 0,
        STATE_START,
        STATE_PROCESS,
        STATE_BRAKE,
        STATE_PRESTOP,
        STATE_STATIC
} state; 

void chassis_write(motor_speed_t left, motor_speed_t right)
{
        /* TODO: insert convertion from units to mm/s or equal */
        state = STATE_STATIC;
        v_left = left;
        v_right = right;
}

void chassis_move(motor_speed_t left, motor_speed_t right, motor_speed_t acc, motor_speed_t acc_div, motor_path_t path)
{
        /* TODO: convertions and acceleration */
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

        min_left = 1;
        min_right = 1;

        v_path = path;
        h_path = path / 2;

        state = STATE_START;
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
                        a_path = path; /* save acceleration path */
                }

                if (path >= h_path) {
                        state = STATE_BRAKE;
                        a_path = path;
                        a_dval = 0;
                }
        } else if (state == STATE_PROCESS) { /* process */
                //v_left = r_left;
                //v_right = r_right;

                if (v_path - a_path <= path) {
                        state = STATE_BRAKE;
                }
        } else if (state == STATE_BRAKE) {
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
                if (abs(v_left) <= abs(min_left) || abs(v_right) <= abs(min_right))
                        state = STATE_PRESTOP;
        } else if (state == STATE_PRESTOP) {
                if (path >= v_path) {
                        state = STATE_STOP;
                        v_left = 0;
                        v_right = 0;
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
