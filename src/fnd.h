/*
 * fnd.h
 *
 * Created: 2026-06-12 오전 10:46:00
 */

#ifndef FND_H_
#define FND_H_

#include "common.h"

#define FND_DATA_DDR DDRC
#define FND_DATA_PORT PORTC

#define FND_DIGIT_DDR DDRB
#define FND_DIGIT_PORT PORTB
#define FND_DIGIT_D1 4
#define FND_DIGIT_D2 5
#define FND_DIGIT_D3 6
#define FND_DIGIT_D4 7

void init_fnd(void);
void fnd_display(WASHING_MACHINE *machine);

#endif /* FND_H_ */
