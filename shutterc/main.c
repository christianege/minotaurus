#include "libscheduler.h"
#include "libuart.h"

/* 9600 baud */
#define UART_BAUD_RATE      9600      

/******************************	LED 0 Timer *****************************/

void shutter_down_switch_off( void )	// dummy to detect double press
{
}
void shutter_up_switch_off (void )		// dummy to detect double press
{
}	
void shutter_stop(void)
{
	uart_puts("> power off \r");
	PORTC &= ~((1<<PC5) | (1<<PC4)); /* set Pin 5 & 4 low, this disables power and release relais */
}

void enable_shutter_power(void)
{
	uart_puts("> power on \r");
	PORTC |= (1<<PC5); /* set Pin 5 high, this enables power */
}

void shutter_down( void )
{
    if( timerremove( shutter_down_switch_off ) )
	{
      timeradd( shutter_down_switch_off, SECONDS( 0.5 ) ); // wait for double press
    }
	else
	{
      return; // double press within 0.5sec
    }
	uart_puts("> moving down!! \r");
	PORTC |= (1<<PC4); /* set Pin 4 high, this enables direction */
	timeradd(enable_shutter_power, SECONDS( 0.5 ));
	timeradd(shutter_stop,SECONDS( 12));
}

void shutter_up( void )
{
    if( timerremove( shutter_up_switch_off ) )
	{
      timeradd( shutter_up_switch_off, SECONDS( 12.6 ) ); // wait for double press
    }
	else
	{
      return; // double press within 0.5sec
    }
	uart_puts("> moving up!! \r");
	PORTC &= ~(1<<PC4); /* set Pin 4 high, this enables direction */
	timeradd(enable_shutter_power, SECONDS( 0.5 ));
	timeradd(shutter_stop,SECONDS( 12));
}



/******************************	LED 1 Timer *****************************/

void light1_off( void ){
  LED_OUTPUT |= 1<<LED1;
}


void light1_switch_off( void )		// dummy function
{
}


void light1_on_off( void )
{
  if( (LED_OUTPUT & 1<<LED1) == 0 ){
    if( timerremove( light1_switch_off ) ){
      timeradd( light1_switch_off, SECONDS( 0.8 ) );
    }else{
      light1_off();
      return;
    }
  }
  LED_OUTPUT &= ~(1<<LED1);
  timerremove( light1_off );
  timeradd( light1_off, SECONDS( 11 ) );
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

uart_puts("-> Starting up .... \r");

  for(;;){				// main loop
    if( f_timer_tick ){
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
