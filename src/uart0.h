/*
 * uart0.h
 *
 * Created: 2026-06-16 오전 9:57:41
 */

#ifndef UART0_H_
#define UART0_H_

#include "common.h"

void init_uart0(void);
void UART0_transmit(uint8_t data);
int uart0_putchar(char c, FILE *stream);

#endif /* UART0_H_ */
