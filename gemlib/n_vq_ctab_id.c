/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vq_ctab_id (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 206,2, 0,0);

	return vdi_intout_long(0);
}
