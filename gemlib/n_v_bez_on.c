/*
 *   NOTE: requires NVDI version 2.10 or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_bez_on (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 11,13, 1,0);

	return vdi_intout[0];
}
