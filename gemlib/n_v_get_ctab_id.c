/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
v_get_ctab_id (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 206,6, 0,0);

	return vdi_intout_long(0);
}
