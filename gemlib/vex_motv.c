#include "gem_vdiP.h"


void
vex_motv (short handle, void *new, void **old)
{
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 126);
	
	*old = vdi_control_ptr(9);
}
