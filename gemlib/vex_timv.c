#include "gem_vdiP.h"


void
vex_timv (short handle, void *time_addr, void **otime_addr, short *time_conv)
{
	vdi_control_ptr(7) = time_addr;
	
	VDI_TRAP_00 (vdi_params, handle, 118);
	
	*otime_addr = vdi_control_ptr(9);
	*time_conv  = vdi_intout[0];
}
