/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vq_max_color (short handle, COLOR_ENTRY * hilite_color)
{
	VDI_TRAP_ESC (vdi_params, handle, 209,2, 0,0);

	*hilite_color = *(COLOR_ENTRY *) & vdi_intout[2];
	
	return vdi_intout_long(0);
}
