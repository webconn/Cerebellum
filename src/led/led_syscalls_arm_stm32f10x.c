/**
 * Cerebellum LED library system calls
 * Arch: ARM (STM32F10x)
 */

#include <lib/cerebellum/board.h>
#include <lib/cerebellum/helpers/arm-stm32f10x/gpio.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define LED_INIT(num) GPIO_INIT_OUT_PP(CONF(CEREBELLUM_BOARD_LEDS_GPIO, num), CONF(CEREBELLUM_BOARD_LEDS_PIN, num))
#define LED_ON(num) GPIO_WRITE_HIGH(CONF(CEREBELLUM_BOARD_LEDS_GPIO, num), CONF(CEREBELLUM_BOARD_LEDS_PIN, num))
#define LED_OFF(num) GPIO_WRITE_LOW(CONF(CEREBELLUM_BOARD_LEDS_GPIO, num), CONF(CEREBELLUM_BOARD_LEDS_PIN, num))
#define LED_WRITESTATE(num) do { if ((state && !CEREBELLUM_BOARD_LEDS_INV_##num) || (!state && CEREBELLUM_BOARD_LEDS_INV_##num)) LED_ON(num); else LED_OFF(num); } while (0)

static inline void _syscall_led_init(void)
{
#if (CEREBELLUM_BOARD_LEDS_NUM >= 1)
        LED_INIT(1);
#endif
#if (CEREBELLUM_BOARD_LEDS_NUM >= 2)
        LED_INIT(2);
#endif
#if (CEREBELLUM_BOARD_LEDS_NUM >= 3)
        LED_INIT(3);
#endif
}

static inline void _syscall_led_write(uint32_t num, uint32_t state)
{
#if (CEREBELLUM_BOARD_LEDS_NUM >= 1)
        if (num == 1)
                LED_WRITESTATE(1);
#endif
#if (CEREBELLUM_BOARD_LEDS_NUM >= 2)
        else if (num == 2)
                LED_WRITESTATE(2);
#endif
#if (CEREBELLUM_BOARD_LEDS_NUM >= 3)
        else if (num == 3)
                LED_WRITESTATE(3);
#endif
}
