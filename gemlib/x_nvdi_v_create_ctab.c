
#include "gemx.h"


COLOR_TAB *
v_create_ctab (int handle, long color_space, unsigned long px_format)
{
	*(long *) &vdi_intin[0] = color_space;
	*(unsigned long *) &vdi_intin[2] = px_format;

	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 4;
	vdi_control[5] = 8;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return (*(COLOR_TAB **) & vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
