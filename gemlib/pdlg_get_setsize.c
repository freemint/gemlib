#include "gem_aesP.h"
#include "gemx.h"


long
pdlg_get_setsize (void)
{
	long l;

	aes_intin[0] = 0;
	aes_control[0] = 204;
	aes_control[1] = 1;
	aes_control[2] = 2;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	l = *(long *) &aes_intout[0];
	return l;
}
