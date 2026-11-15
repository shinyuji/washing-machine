/*
 * uart0.c
 *
 * 디버그 메시지(printf) 출력용 UART0 송신
 */
#include "uart0.h"

void init_uart0(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;			//9600bps (U2X0 = 1)
	UCSR0A |= 1 << U2X0;	//2배속
	UCSR0B |= 1 << TXEN0;	//송신 enable
}

void UART0_transmit(uint8_t data)
{
	while(!(UCSR0A & 1 << UDRE0))	//이전 송신이 끝날 때까지 대기
		;
	UDR0 = data;
}

//printf 출력을 UART0로 연결
int uart0_putchar(char c, FILE *stream)
{
	(void)stream;
	UART0_transmit((uint8_t)c);
	return 0;
}
