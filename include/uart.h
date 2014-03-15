#ifndef ANTARES_LIB_CEREBELLUM_UART_H
#define ANTARES_LIB_CEREBELLUM_UART_H

#include <stdint.h>

void uart_init(void);

void uart_write(uint8_t value);
uint8_t uart_read(void);

#endif
