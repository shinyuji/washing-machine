#include "common.h"
#include "uart0.h"

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(WASHING_MACHINE *machine);

ISR(USART0_RX_vect)
{
	volatile uint8_t data;
	volatile static int i = 0;
	
	data = UDR0;
	
	if (data == '\n' || data == '\r')
	{
		if( (rear + 1) % QUEUE_SIZE == front % QUEUE_SIZE){
			return;
		}
		rx_buff[rear][i] = '\0';
		i = 0;
		rear = (rear + 1) % QUEUE_SIZE;
	}
	else
	{
		if( (rear + 1) % QUEUE_SIZE == front % QUEUE_SIZE){
			return;
		}
		if (i < 20) {
			rx_buff[rear][i++] = data;
		}
	}
}

void init_uart0(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;
	UCSR0A |= 1 << U2X0;
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0;
}

void UART0_transmit(uint8_t data)
{
	while(!(UCSR0A & 1 << UDRE0))
	;
	UDR0 = data;
}

void pc_command_processing(WASHING_MACHINE *machine){
	
	/*
	if(front != rear)
	{
		char clean_buff[20] = {0,};
		int c_idx = 0;

		for(int i = 0; rx_buff[front][i] != '\0' && i < 20; i++) {
			if(rx_buff[front][i] >= '0' && rx_buff[front][i] <= '9') {
				clean_buff[c_idx++] = rx_buff[front][i];
			}
		}
		clean_buff[c_idx] = '\0';

		printf("RX string: %s\n", rx_buff[front]);
		
		if(c_idx > 0) {
			int buff_num = atoi(clean_buff);

			if(mode == 4 || mode == 5 || mode == 6)
			{
				set_sec[time_state] = buff_num;
				printf("Set room[%d]: %d sec\n", time_state, buff_num);
			}
			} else {
			printf("ERR: No digit\n");
		}

		// 사용한 버퍼 클리어
		for(int i = 0; i < 20; i++) {
			rx_buff[front][i] = 0;
		}

		front = (front + 1) % QUEUE_SIZE;
	}
	*/
}