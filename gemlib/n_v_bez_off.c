/*
 *   NOTE: requires NVDI version 2.10 or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_bez_off (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 11,13, 0,0);
}
