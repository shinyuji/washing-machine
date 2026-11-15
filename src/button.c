/*
 * button.c
 *
 * Created: 2026-06-10 오후 1:25:20
 */

#include "button.h"
#include "time.h"

static int get_button(int button_num, int button_pin);

void init_button(void)
{
	BUTTON_DDR &= ~(1 << BUTTON0PIN | 1 << BUTTON1PIN | 1 << BUTTON2PIN | 1 << BUTTON3PIN);
}

static int get_button(int button_num, int button_pin)
{
	// static: 함수를 빠져나와도 버튼별 이전 상태 유지
	static unsigned char button_status[BUTTON_NUMBER] = {BUTTON_RELEASE};

	int current_state;

	// 1. button을 읽는다.
	current_state = BUTTON_PIN & (1 << button_pin);
	// 2. 버튼 상태 check
	if (current_state  && button_status[button_num] == BUTTON_RELEASE)  // 버튼이 처음 눌려진 상태
	{
		_delay_ms(15);  // noise가 지나가기를 기다린다.
		button_status[button_num] =BUTTON_PRESS;
		return 0;     // 아직은 완전히 눌렀다 뗀 상태가 아니다.
	}
	else if (button_status[button_num] == BUTTON_PRESS && current_state == BUTTON_RELEASE)
	{  // 버튼이 이전에 눌려진 상태였으며 지금은 떼어진 상태
		button_status[button_num] = BUTTON_RELEASE;   // 다음 버튼을 체크 하기 위하여 초기화
		_delay_ms(15);  // noise가 지나가기를 기다린다.
		return 1;   // 완전히 1번 눌렀다 뗀 상태로 인정 한다.
	}

	return 0;   // 버튼이 open 상태 이다.
}

void button_event(WASHING_MACHINE *machine){

	//버튼 0이 눌렸을 때
	if (get_button(BUTTON0,BUTTON0PIN))
	{
		switch(machine->mode){
			case MODE_STANDBY:					//대기 모드면
				machine->mode = MODE_WORKING;	//동작 모드로 변경
				machine->working_option = WASH;
				reset_timer_time(machine);		//타이머 시간 초기화
				break;
			case MODE_WORKING:					//동작 모드면
				machine->mode = MODE_STANDBY;	//대기 모드로 변경
				break;
			default:							//설정 모드에서는 무시
				break;
		}
	}

	//버튼 1이 눌렸을 때
	else if (get_button(BUTTON1,BUTTON1PIN))
	{
		if(machine->mode == MODE_STANDBY){		//대기 모드면
			machine->mode = MODE_SETTING;		//세팅 모드로 변경
			machine->setting_option = SET_WASH_TIME;
		}
		else if(machine->mode == MODE_SETTING){		//세팅 모드면

			if(machine->setting_option == SET_SPIN_TIME)
			{
				machine->mode = MODE_STANDBY;
			}
			machine->setting_option = (machine->setting_option + 1) % 3;	//모드 옵션 변경
		}
	}
}
