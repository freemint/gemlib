/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vql_fg_color (short handle, COLOR_ENTRY * fg_color)
{
	VDI_TRAP_ESC (vdi_params, handle, 202,2, 0,0);

	*fg_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
