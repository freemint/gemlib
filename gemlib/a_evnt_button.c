#include "gem_aesP.h"


short
evnt_button (short Clicks, short WhichButton, short WhichState,
             short *Mx, short *My, short *ButtonState, short *KeyState)
{
	aes_intin[0] = Clicks;
	aes_intin[1] = WhichButton;
	aes_intin[2] = WhichState;
	
	AES_TRAP (aes_params, 21, 3,5,0,0);
	
	*Mx          = aes_intout[1];
	*My          = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState    = aes_intout[4];
	
	return aes_intout[0];
}
