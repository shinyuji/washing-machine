#include "common.h"
#include "button.h"
#include "led.h"
#include "pwm.h"
#include "fnd.h"
#include "time.h"
#include "uart0.h"

static void machine_processing(WASHING_MACHINE *machine);

FILE OUTPUT = FDEV_SETUP_STREAM(uart0_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	//모드, 동작 단계, 설정 항목, 설정 시간(세탁·헹굼·탈수, 초), 남은 시간, 모터 방향
	WASHING_MACHINE machine = {MODE_STANDBY, WASH, SET_WASH_TIME, {73, 30, 20}, {0, 0, 0}, FORWARD};

	init_led();
	init_button();
	init_fnd();
	init_uart0();
	init_motor_driver();
	init_timer3_pwm();
	init_timer0();
	reset_timer_time(&machine);

	sei();
	stdout = &OUTPUT;

	while (1)
	{
		button_event(&machine);
		machine_processing(&machine);
	}
}

static void machine_processing(WASHING_MACHINE *machine)
{
	set_timer(machine);
	set_dcmotor(machine);
	set_led(machine);
	fnd_display(machine);
}
