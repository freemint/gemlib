
#include "gem.h"


short
graf_handle (short *Wchar, short *Hchar, short *Wbox, short *Hbox)
{
	aes_control[0] = 77;
	aes_control[1] = 0;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*Wchar = aes_intout[1];
	*Hchar = aes_intout[2];
	*Wbox = aes_intout[3];
	*Hbox = aes_intout[4];
	
	return aes_intout[0];
}
