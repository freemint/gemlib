#include "gem_vdiP.h"


void
vex_curv (short handle, void *new, void **old)
{
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 127);
	
	*old = vdi_control_ptr(9);
}
