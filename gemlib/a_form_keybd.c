#include "gem_aesP.h"


short
form_keybd (OBJECT *Ktree, short Kobject, short Kobnext, short Kchar,
            short *Knxtobject, short *Knxtchar)
{
	aes_intin[0]  = Kobject;
	aes_intin[1]  = Kchar;
	aes_intin[2]  = Kobnext;
	aes_addrin[0] = (long)Ktree;
	
	AES_TRAP (aes_params, 55, 3,3,1,0);
	
	*Knxtobject = aes_intout[1];
	*Knxtchar   = aes_intout[2];
	
	return aes_intout[0];
}
