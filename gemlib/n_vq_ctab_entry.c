/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vq_ctab_entry (short handle, short index, COLOR_ENTRY * color)
{
	vdi_intin[0] = index;

	VDI_TRAP_ESC (vdi_params, handle, 206,1, 0,1);

	*color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
