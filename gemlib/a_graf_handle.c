#include "gem_aesP.h"


short
graf_handle (short *Wchar, short *Hchar, short *Wbox, short *Hbox)
{
	AES_TRAP (aes_params, 77, 0,5,0,0);
	
	*Wchar = aes_intout[1];
	*Hchar = aes_intout[2];
	*Wbox  = aes_intout[3];
	*Hbox  = aes_intout[4];
	
	return aes_intout[0];
}
