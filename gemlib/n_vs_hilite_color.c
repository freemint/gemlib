/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_hilite_color (short handle, long color_space, COLOR_ENTRY * hilite_color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *hilite_color;

	vdi_control[0] = 207;
	vdi_control[1] = 0;
	vdi_control[3] = 6;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	VDI_TRAP (vdi_params, handle, 207, 0,6);

	return vdi_intout[0];
}
