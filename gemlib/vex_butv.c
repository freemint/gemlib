#include "gem_vdiP.h"


void
vex_butv (short handle, void *new, void **old)
{
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 125);
	
	*old = vdi_control_ptr(9);
}
