#include "gem_vdiP.h"


void
vex_butv (short handle, void *new, void **old)
{
	*((void **) (&vdi_control[7])) = new;
	
	VDI_TRAP (vdi_params, handle, 125, 0,0);
	
	*old = *((void **) (&vdi_control[9]));
}
