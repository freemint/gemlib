#include "gem_aesP.h"


short
graf_mkstate (short *Mx, short *My, short *ButtonState, short *KeyState)
{
	AES_TRAP (aes_params, 79, 0,5,0,0);
	
	*Mx          = aes_intout[1];
	*My          = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState    = aes_intout[4];
	
	return aes_intout[0];
}
