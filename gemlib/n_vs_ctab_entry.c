/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_ctab_entry (short handle, short index, long color_space, COLOR_ENTRY * color)
{
	vdi_intin                [0] = index;
	*(long*)       &vdi_intin[1] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[3] = *color;

	VDI_TRAP_ESC (vdi_params, handle, 205,1, 0,7);

	return vdi_intout[0];
}
