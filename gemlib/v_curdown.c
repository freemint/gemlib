/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curdown (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,5, 0,0);
}
