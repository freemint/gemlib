
#include "gemx.h"


void
v_opnbm (int *work_in, MFDB * bitmap, int *handle, int *work_out)
{
#ifndef __MSHORT__
	register int i;

	for (i = 0; i < 20; i++)
		vdi_intin[i] = work_in[i];
#else
	vdi_params.intin = (short *) &work_in[0];
	*((MFDB **) (&vdi_control[7])) = bitmap;
	vdi_params.intout = (short *) &work_out[0];
	vdi_params.ptsout = (short *) &work_out[45];
#endif

	*((MFDB **) (&vdi_control[7])) = bitmap;

	vdi_control[0] = 100;
	vdi_control[1] = 0;
	vdi_control[3] = 20;
	vdi_control[5] = 1;
	vdi_control[6] = *handle;
	vdi (&vdi_params);

#ifndef __MSHORT__
	for (i = 0; i < 45; i++)
		work_out[i] = vdi_intout[i];
	for (i = 0; i < 12; i++)
		work_out[i + 45] = vdi_ptsout[i];
#else
	vdi_params.intin = &vdi_intin[0];
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
#endif
	*handle = vdi_control[6];
}

/*
 * * NOTE: requires EdDI version 1.x or higher
 */
