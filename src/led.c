/*
 * led.c
 *
 * Created: 2026-06-15 오전 11:36:40
 */
#include "led.h"

//초기화 함수
void init_led(void)
{
	DDRA=0xff;  // PORTA 를 출력 모드로 설정
	PORTA=0x00;  // PORTA에 물려있는 led를 all off
}

void set_led(WASHING_MACHINE *machine)
{
	//동작 모드면
	if(machine->mode == MODE_WORKING){
		//동작 모드 옵션에 따라서 LED 점등
		switch(machine->working_option)
		{
			case WASH:
				PORTA = 0b00000001;
				break;
			case RINSE:
				PORTA = 0b00000010;
				break;
			case SPIN:
				PORTA = 0b00000100;
				break;
			default:
				PORTA = 0x00;
				break;
		}
	} else PORTA = 0x00;
}
