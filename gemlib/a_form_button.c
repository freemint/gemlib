#include "gem.h"


short
form_button (OBJECT *Btree, short Bobject, short Bclicks, short *Bnxtobj)
{
	aes_addrin[0] = (long) Btree;
	aes_intin[0] = Bobject;
	aes_intin[1] = Bclicks;
	aes_control[0] = 56;
	aes_control[1] = 2;
	aes_control[2] = 2;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*Bnxtobj = aes_intout[1];
	return aes_intout[0];
}
