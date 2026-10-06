#include "common.h"
#include "button.h"
#include "led.h"
#include "pwm.h"
#include "fnd.h"

extern void UART0_transmit(uint8_t data);
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	WASHING_MACHINE machine = {MODE_STANDBY, WASH, SET_WASH_TIME, {73, 30, 20}, {77, 30, 20}, FORWARD};;

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

void machine_processing(WASHING_MACHINE* machine)
{
	set_timer(machine);
	set_dcmoter(machine);
	set_led(machine);
	fnd_display(machine);
}



