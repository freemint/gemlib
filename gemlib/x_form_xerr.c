#include "gem_aesP.h"
#include "gemx.h"


short
form_xerr (long errcode, char *errfile)
{
	unsigned short *i = (unsigned short *) &errcode;

	aes_intin[0] = i[1];
	aes_intin[1] = i[0];
	aes_addrin[0] = (long) errfile;
	aes_control[0] = 136;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
