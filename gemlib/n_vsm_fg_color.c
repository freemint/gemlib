/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vsm_fg_color (short handle, long color_space, COLOR_ENTRY * fg_color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *fg_color;

	VDI_TRAP_ESC (vdi_params, handle, 200,3, 0,6);

	return vdi_intout[0];
}
