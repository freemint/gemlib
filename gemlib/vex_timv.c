#include "gem_vdiP.h"


void
vex_timv (short handle, void *time_addr, void **otime_addr, short *time_conv)
{
	*((void **) (&vdi_control[7])) = time_addr;
	
	VDI_TRAP (vdi_params, handle, 118, 0,0);
	
	*otime_addr = *((void **) (&vdi_control[9]));
	*time_conv  = vdi_intout[0];
}
