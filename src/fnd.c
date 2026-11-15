/*
 * fnd.c
 */
#include "fnd.h"
#include "time.h"

static void set_fnd_display(WASHING_MACHINE *machine, int digit_select, int *p_index, uint8_t **p_ary);
static void set_fnd_digit_port(int digit_select, uint8_t *digit_port);

void init_fnd(void)
{
	FND_DATA_DDR = 0xff;
	FND_DIGIT_DDR |= 1 << FND_DIGIT_D1 | 1 << FND_DIGIT_D2 | 1 << FND_DIGIT_D3 | 1 << FND_DIGIT_D4;
	FND_DATA_PORT = 0xff;
}

void fnd_display(WASHING_MACHINE *machine)
{
	static int digit_select = 0;

	int index;
	uint8_t *p_ary;
	uint8_t digit_port;

	FND_DATA_PORT = 0xff;
	FND_DIGIT_PORT &= ~( (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) );

	set_fnd_display(machine, digit_select, &index, &p_ary);
	set_fnd_digit_port(digit_select, &digit_port);

	FND_DIGIT_PORT = digit_port;
	FND_DATA_PORT = p_ary[index];

	_delay_ms(1);	//자리마다 1ms씩 표시

	digit_select = (digit_select + 1) % 4;
}

static void set_fnd_display(WASHING_MACHINE *machine, int digit_select, int *p_index, uint8_t **p_ary)
{
	static uint8_t fnd_font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x7f};
	//		a     f     e     d     off
	static uint8_t fnd_font_c1[] = {0xfe, 0xdf, 0xef, 0xf7, 0xff, 0xff, 0xff, 0xff};
	//			off						d     c     b     a
	static uint8_t fnd_font_c2[] = {0xff, 0xff, 0xff, 0xff, 0xf7, 0xfb, 0xfd, 0xfe};

	*p_ary = fnd_font;

	int value = 0;
	int digit_num[4] = { 0, 0, 0, 0 };
	uint32_t ms_count = get_ms_count();

	switch(machine->mode){

		case MODE_STANDBY:
			break;

		case MODE_WORKING:
			value = machine->left_sec[machine->working_option];

			if(value < 60){
				digit_num[0] = value%10;	//1초
				digit_num[1] = value/10%6;	//10초
			}
			else{
				digit_num[0] = value/60%10;	//1분
				digit_num[1] = value/600%6;	//10분
			}

			if(digit_select == 2)		*p_ary = fnd_font_c2;
			else if (digit_select ==3)	*p_ary = fnd_font_c1;

			//세탁·헹굼 중에는 모터 방향에 따라 회전 애니메이션 방향을 바꾼다
			if(machine->working_option == WASH || machine->working_option == RINSE){
				if(machine->motor_dir == BACKWARD){
					digit_num[2] = 7-((ms_count/125) % 8);
				} else {
					digit_num[2] = (ms_count/125) % 8;
				}
				digit_num[3] = digit_num[2];
			} else {
				digit_num[2] = (ms_count/125)%8;
				digit_num[3] = (ms_count/125)%8;
			}

			break;

		case MODE_SETTING:
			value = machine->set_sec[machine->setting_option];

			digit_num[0] = value%10;	//1초
			digit_num[1] = value/10%6;	//10초
			digit_num[2] = value/60%10;	//1분
			digit_num[3] = value/600%6;	//10분
			break;
	}

	*p_index = digit_num[digit_select];
}

static void set_fnd_digit_port(int digit_select, uint8_t *digit_port){
	switch(digit_select)
	{
		case 0:	*digit_port = 0x80;
		break;
		case 1:	*digit_port = 0x40;
		break;
		case 2:	*digit_port = 0x20;
		break;
		case 3: *digit_port = 0x10;
		break;
		default: *digit_port = 0x00;
		break;
	}
}
