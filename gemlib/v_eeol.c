/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_eeol (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,10, 0,0);
}
