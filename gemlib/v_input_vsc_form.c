
#include "gem.h"


void
vsc_form (int handle, int form[])
{
#ifndef __MSHORT__
	short i;

	for (i = 0; i < 37; i++)
		vdi_intin[i] = form[i];
#else
	vdi_params.intin = (short *) &form[0];
#endif

	vdi_control[0] = 111;
	vdi_control[1] = 0;
	vdi_control[3] = 37;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

#ifdef __MSHORT__
	vdi_params.intin = (short *) &vdi_intin[0];
#endif
}
