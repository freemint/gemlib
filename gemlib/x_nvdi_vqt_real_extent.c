
#include "gemx.h"


void
vqt_real_extent (int handle, int x, int y, char *string, int extent[])
{
	short i;

	i = vdi_str2array (string, vdi_intin);
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_control[0] = 240;
	vdi_control[1] = 1;
	vdi_control[3] = i;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	for (i = 0; i < 8; i++)
		extent[i] = vdi_ptsout[i];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
