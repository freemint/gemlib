
#include "gem.h"


void
vex_curv (int handle, void *new, void **old)
{
	*((void **) (&vdi_control[7])) = new;
	vdi_control[0] = 127;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*old = *((void **) (&vdi_control[9]));
}
