/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_exit_cur (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,2, 0,0);
}
