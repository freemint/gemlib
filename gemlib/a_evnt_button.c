
#include "gem.h"


int
evnt_button (int Clicks, int WhichButton, int WhichState, int *Mx, int *My,
	     int *ButtonState, int *KeyState)
{
	aes_intin[0] = Clicks;
	aes_intin[1] = WhichButton;
	aes_intin[2] = WhichState;
	aes_control[0] = 21;
	aes_control[1] = 3;
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
