/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curup (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,4, 0,0);
}
