/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vqm_bg_color (short handle, COLOR_ENTRY * bg_color)
{
	VDI_TRAP_ESC (vdi_params, handle, 203,3, 0,0);

	*bg_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
