
#include "gem.h"


short
evnt_timer (unsigned long Interval)
{
	unsigned short *i = (unsigned short *) &Interval;

	aes_intin[0] = i[1];
	aes_intin[1] = i[0];
	
	aes_control[0] = 24;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
