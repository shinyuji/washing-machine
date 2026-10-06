/*
 * time.c
 *
 * Created: 2026-06-19 오전 7:26:56
 *  Author: kccistc
 */ 

#include "time.h"

void init_timer0(void);
void set_timer(WASHING_MACHINE *machine);
void reset_timer_time(WASHING_MACHINE *machine);

volatile uint32_t ms_count = 0;
volatile uint32_t sec_count = 0;
volatile int motor_dir_switch_time = 10;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	ms_count++;
}

void init_timer0(void)
{
	TCNT0 = 6;
	TCCR0 = 0x00;
	TCCR0 |= 1 << CS02;
	TIMSK |= 1 << TOIE0;
}

void set_timer(WASHING_MACHINE *machine){
	if(ms_count >= 1000){
		ms_count = 0;
		sec_count++;
		//1초가 지났을떄의 동작
		//동작 모드면
		if(machine->mode == MODE_WORKING){
			//해당 동작 모드의 남은 시간이 0보다 크면
			
			//방향 상태 토글
			if(machine->working_option == WASH || machine->working_option == RINSE){
				if(sec_count % motor_dir_switch_time == 0){
					machine->motor_dir = !machine->motor_dir;
				}
			}
			
			if(machine->left_sec[machine->working_option] > 0)
				//1초 줄이기
				machine->left_sec[machine->working_option]--;
			//해당 동작 모드의 남은 시간이 0과 같거나 작으면
			else {
				//탈수 모드면 대기 모드로 전환
				if(machine->working_option >= SPIN){
					machine->mode = MODE_STANDBY;
					machine->working_option = WASH;
				}
				//탈수 모드가 아니면 다음 옵션으로 전환하고 타이머 리셋
				else {
					machine->working_option++;
				}
			}

		}
	}
	
}

void reset_timer_time(WASHING_MACHINE *machine)
{
	for(int i = 0; i < 3; i++){
		machine->left_sec[i] = machine->set_sec[i];
	}
}