/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curhome (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,8, 0,0);
}
