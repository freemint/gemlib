
#include "gemx.h"


short
v_resize_bm (short handle, short width, short height, long byte_width,
	     unsigned char *addr)
{
	vdi_intin[0] = width;
	vdi_intin[1] = height;
	*(long *) &vdi_intin[2] = byte_width;
	*(unsigned char **) &vdi_intin[4] = addr;

	vdi_control[0] = 100;
	vdi_control[1] = 0;
	vdi_control[3] = 6;
	vdi_control[5] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
