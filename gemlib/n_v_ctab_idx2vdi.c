/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_ctab_idx2vdi (short handle, short index)
{
	vdi_intin[0] = index;
	
	VDI_TRAP_ESC (vdi_params, handle, 206,3, 0,1);

	return vdi_intout[0];
}
