
#include "gemx.h"


void
vqt_f_extent (int handle, char *str, int extent[])
{
	short i;

	i = vdi_str2array (str, vdi_intin);
	vdi_control[0] = 240;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	for (i = 0; i < 8; i++)
		extent[i] = vdi_ptsout[i];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
