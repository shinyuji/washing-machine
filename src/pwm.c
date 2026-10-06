/*
 * pwm.c
 *
 * Created: 2026-06-18 오후 2:23:22
 *  Author: kccistc
 */ 

#include "pwm.h"

void set_dcmoter(WASHING_MACHINE* machine);
void dcmotor_off(void);
void dcmotor_on(void);
void init_motor_driver(void);
void init_timer3_pwm(void);

void init_timer3_pwm(void)
{
	DDRE |= (1 << 3) | (1 << 5);
	TCCR3A |= 1 << WGM30;
	TCCR3B |= 1 << WGM32;
	TCCR3A |= 1 << COM3C1;
	TCCR3B |= 1 << CS31 | 1 << CS30;	//분주비 64
	OCR3C = 0;
}

void init_motor_driver(void)
{
	DDRF |= 1 << 6 | 1 << 7;		//PF6, PF7을 출력 모드로 설정
	PORTF &= ~(1 << 6 | 1 << 7);	//PE6, PE7의 출력 값 reset - 0으로 set
	PORTF |= 1 << 6;					//정회전
}

//*추가
void dcmotor_on(void){
	OCR3C = 100;
}
void dcmotor_off(void){
	OCR3C = 0;
}

//모터 동작 함수
void set_dcmoter(WASHING_MACHINE* machine)
{
	static int last_dir = FORWARD;
	if(machine->mode == MODE_WORKING){
		if (machine->motor_dir != last_dir){
			dcmotor_direction_switch(machine);
			last_dir = machine->motor_dir;
		}
		dcmotor_on();
	} else dcmotor_off();
}

//모터 방향 회전 함수
void dcmotor_direction_switch(WASHING_MACHINE *machine){
	PORTF &= ~(1<<6 | 1<<7);	//reset
	if(machine->motor_dir == FORWARD)
		PORTF |= 1<<6;		//정회전
	else PORTF |= 1<< 7;	//역회전
}