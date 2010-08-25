#include "libscheduler.h"

uchar get_key_press( uchar key_mask )
{
  cli();
  key_mask &= key_press;			// read key(s)
  key_press ^= key_mask;			// clear key(s)
  sei();
  return key_mask;
}
