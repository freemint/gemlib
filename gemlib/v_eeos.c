/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_eeos (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,9, 0,0);
}
