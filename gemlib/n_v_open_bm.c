
#include "gemx.h"


short
v_open_bm (short base_handle, GCBITMAP * bitmap, short color_flags,
	   short unit_flags, short pixel_width, short pixel_height)
{
	vdi_intin[0] = color_flags;
	vdi_intin[1] = unit_flags;
	vdi_intin[2] = pixel_width;
	vdi_intin[3] = pixel_height;

	vdi_control[0] = 100;
	vdi_control[1] = 0;
	vdi_control[3] = 4;
	vdi_control[5] = 3;
	vdi_control[6] = base_handle;
	*(GCBITMAP **) & vdi_control[7] = bitmap;
	vdi (&vdi_params);

	return vdi_control[6];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
