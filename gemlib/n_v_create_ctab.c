/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


COLOR_TAB *
v_create_ctab (short handle, long color_space, unsigned long px_format)
{
	*(long*)          &vdi_intin[0] = color_space;
	*(unsigned long *)&vdi_intin[2] = px_format;

	VDI_TRAP_ESC (vdi_params, handle, 206,8, 0,4);

	return *(COLOR_TAB**)&vdi_intout[0];
}
