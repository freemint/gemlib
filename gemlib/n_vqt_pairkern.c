
#include "gemx.h"


void
vqt_pairkern (short handle, short ch1, short ch2, long *x, long *y)
{
	vdi_intin[0] = ch1;
	vdi_intin[1] = ch2;
	vdi_control[0] = 235;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*x = *((long *) (&vdi_ptsout[0]));
	*y = *((long *) (&vdi_ptsout[2]));
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
