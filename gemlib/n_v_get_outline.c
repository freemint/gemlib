
#include "gemx.h"


int
v_get_outline (int handle, int index, int x_offset, int y_offset, short *pts,
	       char *flags, int max_pts)
{
	vdi_intin[0] = index;
	vdi_intin[1] = max_pts;
	*(short **) &vdi_intin[2] = pts;
	*(char **) &vdi_intin[4] = flags;
	vdi_intin[6] = x_offset;
	vdi_intin[7] = y_offset;

	vdi_control[0] = 243;
	vdi_control[1] = 0;
	vdi_control[3] = 8;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
