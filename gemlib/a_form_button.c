#include "gem_aesP.h"


short
form_button (OBJECT *Btree, short Bobject, short Bclicks, short *Bnxtobj)
{
	aes_intin[0]  = Bobject;
	aes_intin[1]  = Bclicks;
	aes_addrin[0] = (long)Btree;
	
	AES_TRAP (aes_params, 56, 2,2,1,0);
	
	*Bnxtobj = aes_intout[1];
	
	return aes_intout[0];
}
