
#include "gemx.h"


void
vq_scrninfo (int handle, int *work_out)
{
#ifndef __MSHORT__
	register short i;
#else
	vdi_params.intout = (short *) &work_out[0];
#endif

	vdi_intin[0] = 2;
	vdi_control[0] = 102;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

#ifndef __MSHORT__
	for (i = 0; i < 273; i++)
		work_out[i] = vdi_intout[i];
#else
	vdi_params.intout = &vdi_intout[0];
#endif
}

/*
 * * NOTE: requires EdDI version 1.x or higher
 */
