/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_max_color (short handle, long color_space, COLOR_ENTRY * min_color)
{
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *min_color;

	VDI_TRAP_ESC (vdi_params, handle, 207,2, 0,6);

	return vdi_intout[0];
}
