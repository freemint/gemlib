/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_hardcopy (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,17, 0,0);
}
