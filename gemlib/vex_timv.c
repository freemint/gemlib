
#include "gem.h"


void
vex_timv (short handle, void *time_addr, void **otime_addr, short *time_conv)
{
	*((void **) (&vdi_control[7])) = time_addr;
	vdi_control[0] = 118;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*otime_addr = *((void **) (&vdi_control[9]));
	*time_conv = vdi_intout[0];
}
