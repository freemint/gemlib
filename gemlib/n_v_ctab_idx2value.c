/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


unsigned long
v_ctab_idx2value (short handle, short index)
{
	vdi_intin[0] = index;

	VDI_TRAP_ESC (vdi_params, handle, 206,5, 0,1);

	return *(unsigned long *)&vdi_intout[0];
}
