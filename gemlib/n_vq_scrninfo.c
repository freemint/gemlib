
#include "gemx.h"


void
vq_scrninfo (short handle, short *work_out)
{
	vdi_params.intout = &work_out[0];

	vdi_intin[0] = 2;
	vdi_control[0] = 102;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 1;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_params.intout = &vdi_intout[0];
}

/*
 * * NOTE: requires EdDI version 1.x or higher
 */
