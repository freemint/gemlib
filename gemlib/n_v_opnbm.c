
#include "gemx.h"


void
v_opnbm (short *work_in, MFDB *bitmap, short *handle, short *work_out)
{
	vdi_params.intin = &work_in[0];
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	vdi_control[0] = 100;
	vdi_control[1] = 0;
	vdi_control[3] = 20;
	vdi_control[5] = 1;
	vdi_control[6] = *handle;
	*((MFDB **) (&vdi_control[7])) = bitmap;

	vdi (&vdi_params);

	vdi_params.intin = &vdi_intin[0];
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
	
	*handle = vdi_control[6];
}

/*
 * * NOTE: requires EdDI version 1.x or higher
 */
