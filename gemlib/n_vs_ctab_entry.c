
#include "gemx.h"


short
vs_ctab_entry (short handle, short index, long color_space, COLOR_ENTRY * color)
{
	vdi_intin[0] = index;
	*(long *) &vdi_intin[1] = color_space;
	*(COLOR_ENTRY *) & vdi_intin[3] = *color;

	vdi_control[0] = 205;
	vdi_control[1] = 0;
	vdi_control[3] = 7;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
