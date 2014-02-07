#include <lib/cerebellum/led.h>
#include <avr/io.h>

static void leds_init(void);
static void leds_write(creg_u8);

static uint8_t is_init = 0;

static struct _cerebellum_reg_struct_u8 _CR_LEDS = {
        .data = 0,
        .read = 0,
        .write = leds_write
};

creg_u8 CR_LEDS = &_CR_LEDS;

static void leds_write(creg_u8 reg)
{
        if (!is_init)
                leds_init();

        if (reg->data & 1) {
                PORTB |= 1;
        } else {
                PORTB &= ~1;
        }
}

static void leds_init(void)
{
        DDRB |= 1;
        is_init = 1;
}
