
#include "gemx.h"


long
vqm_bg_color (short handle, COLOR_ENTRY * fg_color)
{
	vdi_control[0] = 203;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 3;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	*fg_color = *(COLOR_ENTRY *) & vdi_intout[2];
	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
