/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vsl_bg_color (short handle, long color_space, COLOR_ENTRY * bg_color)
{

	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *bg_color;

	VDI_TRAP_ESC (vdi_params, handle, 201,2, 0,6);

	return vdi_intout[0];
}
