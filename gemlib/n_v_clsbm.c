/*
 *   NOTE: requires EdDI version 1.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_clsbm (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 101,1, 0,0);
}
