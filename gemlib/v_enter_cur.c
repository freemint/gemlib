/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_enter_cur (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,3, 0,0);
}
