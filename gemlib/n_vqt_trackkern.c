
#include "gemx.h"


void
vqt_trackkern (int handle, long *x, long *y)
{
	vdi_control[0] = 234;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*x = *((long *) (&vdi_ptsout[0]));
	*y = *((long *) (&vdi_ptsout[2]));
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
