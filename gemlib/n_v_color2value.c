/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


unsigned long
v_color2value (short handle, long color_space, COLOR_ENTRY * color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *color;

	VDI_TRAP (vdi_params, handle, 204, 0,6);

	return *(unsigned long *)&vdi_intout[0];
}
