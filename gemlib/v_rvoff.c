/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_rvoff (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,14, 0,0);
}
