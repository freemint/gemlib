/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_delete_ctab (short handle, COLOR_TAB * ctab)
{
	vdi_intin_ptr(0) = ctab;

	VDI_TRAP_ESC (vdi_params, handle, 206,9, 0,2);

	return vdi_intout[0];
}
