#include <lib/cerebellum/stepper.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* TODO: configure feature */

void stepper_init()
{
        /* Configure timer */
#if defined(CONFIG_MCU_ATMEGA32U4)
#if defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_1)
        TCCR1A = (1<<WGM10);
        TCCR1B = (1<<WGM12) | (1<<CS10);
        TIMSK1 = (1<<TOIE1);
#elif defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_3)
        TCCR3A = (1<<WGM30);
        TCCR3B = (1<<WGM32) | (1<<CS30);
        TIMSK3 = (1<<TOIE3);
#else
#error "Your MCU and Timer/Counter is not implemented; leave feature request"
#endif
#endif
        
        /* Configure GPIO */
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 1
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_ENABLE);
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_1);
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_1);
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 2
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_2);
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_2);
#endif
#if CONFIG_LIB_CEREBELLUM_STEPPER_NUM >= 3
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_STEP_3);
        GPIO_INIT_OUT(CONFIG_LIB_CEREBELLUM_STEPPER_DIR_3);
#endif
}

#if defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_0)
ISR(TIMER0_OVF_vect)
#elif defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_1)
ISR(TIMER1_OVF_vect)
#elif defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_2)
ISR(TIMER2_OVF_vect)
#elif defined(CONFIG_LIB_CEREBELLUM_STEPPER_TIMER_3)
ISR(TIMER3_OVF_vect)
#endif
{
        GPIO_WRITE_LOW(GPB0);
        stepper_interrupt();
        GPIO_WRITE_HIGH(GPB0);
}
