#include "gem_aesP.h"
#include "gemx.h"


void
edit_get_sel (OBJECT *tree, short obj, char **bsel, char **esel)
{
	aes_intin[0] = obj;
	aes_intin[1] = 8;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*bsel = (char *)aes_addrout[0];
	*esel = (char *)aes_addrout[1];
}
