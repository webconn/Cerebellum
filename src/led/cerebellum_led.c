#include <lib/cerebellum/led.h>

static uint8_t init = 0;

#ifdef CONFIG_ARCH_ANTARES
#include <arch/antares.h>
ANTARES_INIT_LOW(led_init)
#else
static inline void led_init(void)
#endif
{
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_1
        gpio_init(CONFIG_LIB_CEREBELLUM_LEDS_1, GPIO_MODE_OUT);
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_2
        gpio_init(CONFIG_LIB_CEREBELLUM_LEDS_2, GPIO_MODE_OUT);
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_3
        gpio_init(CONFIG_LIB_CEREBELLUM_LEDS_3, GPIO_MODE_OUT);
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_4
        gpio_init(CONFIG_LIB_CEREBELLUM_LEDS_4, GPIO_MODE_OUT);
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_5
        gpio_init(CONFIG_LIB_CEREBELLUM_LEDS_5, GPIO_MODE_OUT);
#endif
        init = 1;
}

void led_write(led_t led, led_state_t state)
{
        if (!init)
                led_init();
        
        switch (led) {
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_1
                case 1:
                        gpio_write(CONFIG_LIB_CEREBELLUM_LEDS_1, state);    
                        break;
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_2
                case 2:
                        gpio_write(CONFIG_LIB_CEREBELLUM_LEDS_2, state);    
                        break;
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_3
                case 3:
                        gpio_write(CONFIG_LIB_CEREBELLUM_LEDS_3, state);    
                        break;
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_4
                case 4:
                        gpio_write(CONFIG_LIB_CEREBELLUM_LEDS_4, state);    
                        break;
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_5
                case 5:
                        gpio_write(CONFIG_LIB_CEREBELLUM_LEDS_5, state);    
                        break;
#endif
        }
        /* TODO: assert_failed() here */
}

led_state_t led_read(led_t led)
{
        if (!init)
                led_init();
        
        switch (led) {
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_1
                case 1:
                        return gpio_read(CONFIG_LIB_CEREBELLUM_LEDS_1);    
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_2
                case 2:
                        return gpio_read(CONFIG_LIB_CEREBELLUM_LEDS_2);    
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_3
                case 3:
                        return gpio_read(CONFIG_LIB_CEREBELLUM_LEDS_3);    
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_4
                case 4:
                        return gpio_read(CONFIG_LIB_CEREBELLUM_LEDS_4);    
#endif
#ifdef CONFIG_LIB_CEREBELLUM_LEDS_5
                case 5:
                        return gpio_read(CONFIG_LIB_CEREBELLUM_LEDS_5);    
#endif
        }

        /* TODO: assert_failed() here */
        return 0;
}

void led_on(led_t led)
{
        led_write(led, LED_ON);
}

void led_off(led_t led)
{
        led_write(led, LED_OFF);
}

void led_toggle(led_t led)
{
        led_write(led, !led_read(led));
}
