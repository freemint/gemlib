
#include "gemx.h"


long
vql_fg_color (int handle, COLOR_ENTRY * fg_color)
{
	vdi_control[0] = 202;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	*fg_color = *(COLOR_ENTRY *) & vdi_intout[2];
	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
