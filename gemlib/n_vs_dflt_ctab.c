/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_dflt_ctab (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 205,2, 0,0);

	return vdi_intout[0];
}
