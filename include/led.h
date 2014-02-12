#ifndef ANTARES_LIB_CEREBELLUM_LED_H
#define ANTARES_LIB_CEREBELLUM_LED_H

#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/board.h>

typedef uint8_t led_t;

typedef enum {
        LED_ON = 1,
        LED_OFF = 0
} led_state_t;

void led_write(led_t led, led_state_t state);
led_state_t led_read(led_t led);

void led_off(led_t led);
void led_on(led_t led);
void led_toggle(led_t led);

#endif
