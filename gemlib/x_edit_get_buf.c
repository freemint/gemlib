#include "gem_aesP.h"
#include "gemx.h"


short
edit_get_buf (OBJECT *tree, short obj, char **buf, long *buflen, long *txtlen)
{
	aes_intin[0] = obj;
	aes_intin[1] = 0;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 5;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*buf = (char *) aes_addrout[0];
	*buflen = *((long *) (aes_intout+1));
	*txtlen = *((long *) (aes_intout+3));
	return aes_intout[0];
}
