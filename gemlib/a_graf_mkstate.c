
#include "gem.h"


short
graf_mkstate (short *Mx, short *My, short *ButtonState, short *KeyState)
{
	aes_control[0] = 79;
	aes_control[1] = 0;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*Mx = aes_intout[1];
	*My = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState = aes_intout[4];
	
	return aes_intout[0];
}
