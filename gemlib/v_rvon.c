/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_rvon (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,13, 0,0);
}
