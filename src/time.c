/*
 * time.c
 *
 * Created: 2026-06-19 오전 7:26:56
 */

#include "time.h"
#include <util/atomic.h>

#define MOTOR_DIR_SWITCH_SEC 10	//세탁·헹굼 중 정·역회전 전환 주기(초)

static volatile uint32_t ms_count = 0;	//Timer0 인터럽트에서 1ms마다 증가
static uint32_t sec_count = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;	//6~256: 250 count = 1ms
	ms_count++;
}

void init_timer0(void)
{
	TCNT0 = 6;
	TCCR0 = 0x00;
	TCCR0 |= 1 << CS02;		//64분주 (16MHz / 64 = 250kHz)
	TIMSK |= 1 << TOIE0;	//Timer0 overflow 인터럽트 enable
}

//인터럽트와 공유하는 32bit 값을 한 번에 읽기
uint32_t get_ms_count(void)
{
	uint32_t ms;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { ms = ms_count; }
	return ms;
}

void set_timer(WASHING_MACHINE *machine){
	if(get_ms_count() >= 1000){
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { ms_count = 0; }
		sec_count++;
		//1초가 지났을떄의 동작
		//동작 모드면
		if(machine->mode == MODE_WORKING){
			//방향 상태 토글
			if(machine->working_option == WASH || machine->working_option == RINSE){
				if(sec_count % MOTOR_DIR_SWITCH_SEC == 0){
					machine->motor_dir = !machine->motor_dir;
				}
			}

			//해당 단계의 남은 시간이 있으면 1초 줄이기
			if(machine->left_sec[machine->working_option] > 0)
				machine->left_sec[machine->working_option]--;
			//해당 동작 모드의 남은 시간이 0과 같거나 작으면
			else {
				//탈수 모드면 대기 모드로 전환
				if(machine->working_option >= SPIN){
					machine->mode = MODE_STANDBY;
					machine->working_option = WASH;
				}
				//탈수 모드가 아니면 다음 단계로 전환
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
