
#include "gem.h"


int
form_keybd (void *Ktree, int Kobject, int Kobnext, int Kchar, int *Knxtobject,
	    int *Knxtchar)
{
	aes_addrin[0] = (long) Ktree;
	aes_intin[0] = Kobject;
	aes_intin[1] = Kchar;
	aes_intin[2] = Kobnext;
	aes_control[0] = 55;
	aes_control[1] = 3;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*Knxtobject = aes_intout[1];
	*Knxtchar = aes_intout[2];
	return aes_intout[0];
}
