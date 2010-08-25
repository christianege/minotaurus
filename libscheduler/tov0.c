#include "libscheduler.h"


uchar key_state;			// debounced and inverted key state:
					// bit = 1: key pressed
uchar key_press;			// key press detect or repeat

uchar f_timer_tick;


SIGNAL (SIG_OVERFLOW0)
{
  static char ct0, ct1;
  char i;

  i = key_state ^ ~KEY_INPUT;		// key changed ?
  ct0 = ~( ct0 & i );			// reset or count ct0
  ct1 = ct0 ^ ct1 & i;			// reset or count ct1
  i &= ct0 & ct1;			// count until roll over ?
  key_state ^= i;			// then toggle debounced state
  key_press |= key_state & i;		// 0->1: key press detect

  f_timer_tick = 1;
}
