/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
v_color2nearest (short handle, long color_space, COLOR_ENTRY * color,
                 COLOR_ENTRY * nearest_color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *color;

	VDI_TRAP_ESC (vdi_params, handle, 204,2, 0,6);

	*nearest_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
