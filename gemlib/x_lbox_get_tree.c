#include "gemx.h"
#include "gem_aesP.h"


OBJECT *
lbox_get_tree (LIST_BOX *box)
{
	aes_intin[0] = 1;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 174;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (OBJECT *) aes_addrout[0];
}
