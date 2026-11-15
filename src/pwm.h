/*
 * pwm.h
 *
 * Created: 2026-06-18 오후 2:23:10
 */

#ifndef PWM_H_
#define PWM_H_

#include "common.h"

void init_timer3_pwm(void);
void init_motor_driver(void);
void set_dcmotor(WASHING_MACHINE *machine);

#endif /* PWM_H_ */
