#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef LIBSCHEDULER_20100902_H__
#define LIBSCHEDULER_20100902_H__


#define TIMERTICK	(F_CPU / 256 / 256)	// timer ticks per second

#define SECONDS(x)	((uint)(TIMERTICK * x + 0.5))

#define uchar unsigned char
#define uint unsigned int
#define bit uchar
#define idata
#define code

typedef void (code *funcp)(void);

//#define t_res		uchar		// define time resolution  8 bit
#define t_res		uint		// define time resolution 16 bit


#define KEY_INPUT	PIND


#define LED_OUTPUT	PORTB
#define LED0		PB0
#define LED1		PB1
#define LED2		PB2
#define LED3		PB3
#define LED4		PB4


extern uchar key_state;		// debounced and inverted key state:
				// bit = 1: key pressed
extern uchar key_press;		// key press detect or repeat

extern uchar f_timer_tick;	// timer flag


extern uchar get_key_press( uchar key_mask );

void timertick(void);

bit timeradd( funcp func, t_res delay );

bit timerremove( funcp func );

void timerinit(void);

#endif /* LIBSCHEDULER_20100902_H__ */
