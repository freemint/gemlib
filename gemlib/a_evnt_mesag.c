
#include "gem.h"


int
evnt_mesag (int MesagBuf[])
{
#ifndef __MSHORT__
	short dummy[8];
	register int i;

	aes_addrin[0] = (long) &dummy[0];
#else
	aes_addrin[0] = (long) MesagBuf;
#endif

	aes_control[0] = 23;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);

#ifndef __MSHORT__
	if (MesagBuf != (int *) 0)
		for (i = 0; i < 8; i++)
			MesagBuf[i] = dummy[i];
#endif

	return aes_intout[0];
}
