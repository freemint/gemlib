/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curright (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,6, 0,0);
}
