/*
 * time.h
 *
 * Created: 2026-06-19 오전 7:26:48
 */

#ifndef TIME_H_
#define TIME_H_

#include "common.h"

void init_timer0(void);
uint32_t get_ms_count(void);
void set_timer(WASHING_MACHINE *machine);
void reset_timer_time(WASHING_MACHINE *machine);

#endif /* TIME_H_ */
