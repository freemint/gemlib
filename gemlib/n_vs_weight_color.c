/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_weight_color (short handle, long color_space, COLOR_ENTRY * weight_color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *weight_color;

	VDI_TRAP_ESC (vdi_params, handle, 207,3, 0,6);

	return vdi_intout[0];
}
