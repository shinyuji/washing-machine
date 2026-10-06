#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU 16000000UL  // 16MHz
#include <avr/io.h>  // PORTA PORTB PORTD... IO관련 reg가 들어 있다.
#include <util/delay.h>  // _delay_ms _delay_us 등
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	MODE_STANDBY,
	MODE_WORKING,
	MODE_SETTING
} MODE;

typedef enum {
	WASH,
	RINSE,
	SPIN,
} WORKING_OPTION ;

typedef enum {
	SET_WASH_TIME,
	SET_RINSE_TIME,
	SET_SPIN_TIME
} SETTING_OPTION;

typedef enum {
	FORWARD,
	BACKWARD
} MOTOR_DIRECTION;
typedef struct {
	
	MODE mode;	//대기, 동작, 세팅
	
	WORKING_OPTION working_option;	//동작 - 세탁, 헹굼, 탈수
	SETTING_OPTION setting_option;	//세팅 - 세탁, 헹굼, 탈수
	
	int set_sec[3];		//타이머 세팅 시간
	int left_sec[3];	//타이머
	
	MOTOR_DIRECTION	motor_dir;//모터 회전 방향

} WASHING_MACHINE;


#endif /* COMMON_H_ */