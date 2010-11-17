#include "libscheduler.h"
#include "libuart.h"
#include "shutter.h"

#include <stdio.h>

/* 9600 baud */
#define UART_BAUD_RATE      9600      

static int uart_putchar(char c, FILE *stream);

/* redirection of stdout ( part 1) */ 
static FILE shutterstdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

/* dummy wrapper */
static int uart_putchar(char c, FILE *stream)
{
	uart_putc(c);
	return 0;
}

void initioports(void)
{
    DDRC = 0xff; /* All Port C Pins are outputs */
    PORTC = 0x00; /* clear all Pins */

    DDRB &= ~(  (1 << PD3) | (1 << PD4) | (1 << PD5) );   /* alle Pin 3,4 und 5 von Port D als Eingang */

    PORTD |= ((1 << PD3) | (1<<PD4) | (1<<PD5)); /* interne Pull-Ups an Port-Pins 3,4 und 5  aktivieren */
}

/******************************	Main ************************************/

int main( void )
{
	key_state = 0;
	key_press = 0;

	TCCR0 = 1<<CS02;			//divide by 256 * 256
	TIMSK = 1<<TOIE0;			//enable timer interrupt

	initioports();

	timerinit();
	
	/*
	*  Initialize UART library, pass baudrate and AVR cpu clock
	*  with the macro 
	*  UART_BAUD_SELECT() (normal speed mode )
	*  or 
	*  UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
	*/
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 

	sei();

	/* redirection of stdout to use printf over uart */
	stdout = &shutterstdout;

uart_puts("-> Starting up .... \r");

  for(;;)
  {				// main loop
    if( f_timer_tick )
	{
		f_timer_tick = 0;
		timertick();
    }
  
  	if( get_key_press( 1<<PD3 ) )
    {
		uart_puts("> PD3 pressed \r");
		shutter_down(  );
    }
  
  	if( get_key_press( 1<<PD4 ) )
    {
		uart_puts("> PD4 pressed \r");
		shutter_up(  );
    }
  
  	if( get_key_press( 1<<PD5 ) )
    {
		uart_puts("> PD5 pressed \r");
		timerremove(shutter_stop);
		shutter_stop();
    }
  }
}

