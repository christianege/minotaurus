#include <avr/io.h>
#include <stdio.h>

#include "libscheduler.h"

void shutter_down_switch_off( void )	/* dummy to detect double press */
{
}

void shutter_up_switch_off (void )		/* dummy to detect double press */
{
}	

void shutter_stop(void)
{
	printf("> power off \r");
	PORTC &= ~((1<<PC5) | (1<<PC4)); /* set Pin 5 & 4 low, this disables power 
										and releases relays 
									  */
}

void enable_shutter_power(void)
{
	printf("> power on \r");
	PORTC |= (1<<PC5);				/* set Pin 5 high, this enables power */
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
	printf("> moving down!! \r");
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
	printf("> moving up!! \r");
	PORTC &= ~(1<<PC4); /* set Pin 4 high, this enables direction */
	timeradd(enable_shutter_power, SECONDS( 0.5 ));
	timeradd(shutter_stop,SECONDS( 12));
}

