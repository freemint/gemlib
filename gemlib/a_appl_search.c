
#include "gem.h"


int
appl_search (int mode, char *fname, int *type, int *ap_id)
{
	aes_intin[0] = mode;
	aes_addrin[0] = (long) fname;
	aes_control[0] = 18;
	aes_control[1] = 1;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*type = aes_intout[1];
	*ap_id = aes_intout[2];
	return aes_intout[0];
}
