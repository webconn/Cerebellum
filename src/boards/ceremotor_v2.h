#ifndef ANTARES_LIB_CONTRIB_CEREBELLUM_BOARD_CEREMOTOR_V2_H
#define ANTARES_LIB_CONTRIB_CEREBELLUM_BOARD_CEREMOTOR_V2_H

#define CEREBELLUM_BOARD CereMotor v2

/**
 * I. LEDs definition
 */

#define CEREBELLUM_BOARD_LEDS_GPIO_1 GPIOA
#define CEREBELLUM_BOARD_LEDS_RCC_1 RCC_APB2Periph_GPIOA
#define CEREBELLUM_BOARD_LEDS_PIN_1 5

#define CEREBELLUM_BOARD_LEDS_GPIO_2 GPIOC
#define CEREBELLUM_BOARD_LEDS_RCC_2 RCC_APB2Periph_GPIOC
#define CEREBELLUM_BOARD_LEDS_PIN_2 15

#define CEREBELLUM_BOARD_LEDS_GPIO_3 GPIOC
#define CEREBELLUM_BOARD_LEDS_RCC_3 RCC_APB2Periph_GPIOC
#define CEREBELLUM_BOARD_LEDS_PIN_3 10

/**
 * II. Extra board features
 *
 * List of board's extra features:
 *
 * 1. 2 x DC motor driver channels
 *      or
 *    3 x Stepper driver channels
 *
 * 2. 2 x differential encoder channels
 */

/** 
 * II. 1. DC motor driver
 */
#define CEREBELLUM_BOARD_DCM_TIMER TIM4
#define CEREBELLUM_BOARD_DCM_TIMER_RCC_APB1

#endif
