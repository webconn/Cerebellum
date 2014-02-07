#include <lib/cerebellum/led.h>
#include <arch/antares.h>

#ifdef CONFIG_CONTRIB_CEREBELLUM_DEBUG
#include <lib/printk.h>
#endif

#if defined(CONFIG_ARCH_AVR)
#include "led_syscalls_avr.c"
#elif defined(CONFIG_STM32F10X)
#include "led_syscalls_arm_stm32f10x.c"
#endif

static void cerebellum_leds_init(void);
static void cerebellum_leds_write(creg_u8);

static uint8_t is_init = 0;

static struct _cerebellum_reg_struct_u8 _CR_LEDS = {
        .data = 0,
        .read = NULL,
        .write = cerebellum_leds_write
};

creg_u8 CR_LEDS = &_CR_LEDS;

static void cerebellum_leds_write(creg_u8 reg)
{
        if (!is_init)
                cerebellum_leds_init();

        int i;
        for (i = 0; i < CEREBELLUM_BOARD_LEDS_NUM; i++) {
                if (reg->data & (1 << i))
                        _syscall_led_write(i+1, 1);
                else
                        _syscall_led_write(i+1, 0);
        }
}

#ifdef CONFIG_ANTARES_STARTUP
ANTARES_INIT_LOW(cerebellum_leds_init)
#else
static void cerebellum_leds_init(void)
#endif
{
        _syscall_led_init();

#ifdef CONFIG_CONTRIB_CEREBELLUM_DEBUG
        printk("Cerebellum: LEDs initialization complete. Number of LEDs: %d\n", CEREBELLUM_BOARD_LEDS_NUM);
#endif
        is_init = 1;
}
