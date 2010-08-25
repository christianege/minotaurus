#include "libscheduler.h"

/******************************	LED 0 Timer *****************************/

void light0_off( void ){
  LED_OUTPUT |= 1<<LED0;		// LED off (low active)
}


void light0_switch_off( void )		// dummy to detect double press
{
}


void light0_on_off( void )
{
  if( (LED_OUTPUT & 1<<LED0) == 0 ){
    if( timerremove( light0_switch_off ) ){
      timeradd( light0_switch_off, SECONDS( 0.8 ) ); // wait for double press
    }else{
      light0_off();			// double press within 0.8sec
      return;
    }
  }
  LED_OUTPUT &= ~(1<<LED0);		// LED on (low active)
  timerremove( light0_off );
  timeradd( light0_off, SECONDS( 10 ) );	// start or start again
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


/******************************	Main ************************************/

int main( void )
{
  key_state = 0;
  key_press = 0;

  TCCR0 = 1<<CS02;			//divide by 256 * 256
  TIMSK = 1<<TOIE0;			//enable timer interrupt

  DDRB = 0xFF;
  LED_OUTPUT = 0xFF;

  timerinit();
  sei();

  for(;;){				// main loop
    if( f_timer_tick ){
      f_timer_tick = 0;
      timertick();
    }
    if( get_key_press( 1<<LED0 ) )
      light0_on_off();			// timer for LED0
    if( get_key_press( 1<<LED1 ) )
      light1_on_off();			// timer for LED1
    if( get_key_press( 1<<LED2 ) )
      LED_OUTPUT ^= 1<<LED2;		// toggle LED2 on key press
  }
}
