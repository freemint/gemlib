/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_ctab_vdi2idx (short handle, short vdi_index)
{
	vdi_intin[0] = vdi_index;

	VDI_TRAP_ESC (vdi_params, handle, 206,4, 0,1);

	return vdi_intout[0];
}
