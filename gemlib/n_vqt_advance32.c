
#include "gemx.h"


void
vqt_advance32 (short handle, short ch, long *advx, long *advy)
{
	vdi_intin[0] = ch;
	vdi_control[0] = 247;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*advx = *((long *) (&vdi_ptsout[4]));
	*advy = *((long *) (&vdi_ptsout[6]));
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
