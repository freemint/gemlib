
#include "gemx.h"


int
vq_ctab (int handle, long ctab_length, COLOR_TAB * ctab)
{
	*(long *) &vdi_intin[0] = ctab_length;
	vdi_params.intout = (short *) ctab;
	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	vdi_params.intout = vdi_intout;

	if (vdi_control[4])
		return 1;
	else
		return 0;
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
