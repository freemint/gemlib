
#include "gem.h"


short
evnt_mouse (short EnterExit, short InX, short InY, short InW, short InH,
	    short *OutX, short *OutY, short *ButtonState, short *KeyState)
{
	aes_intin[0] = EnterExit;
	aes_intin[1] = InX;
	aes_intin[2] = InY;
	aes_intin[3] = InW;
	aes_intin[4] = InH;
	
	aes_control[0] = 22;
	aes_control[1] = 5;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*OutX = aes_intout[1];
	*OutY = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState = aes_intout[4];
	
	return aes_intout[0];
}
