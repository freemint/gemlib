/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_open_bm (short base_handle, GCBITMAP * bitmap, short color_flags,
           short unit_flags, short pixel_width, short pixel_height)
{
	vdi_intin[0] = color_flags;
	vdi_intin[1] = unit_flags;
	vdi_intin[2] = pixel_width;
	vdi_intin[3] = pixel_height;

	vdi_control_ptr(7) = bitmap;
	VDI_TRAP_ESC (vdi_params, base_handle, 100,3, 0,4);

	return vdi_control[6];
}
