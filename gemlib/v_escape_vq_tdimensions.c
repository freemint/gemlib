
#include "gem.h"


void
vq_tdimensions (int handle, int *xdimension, int *ydimension)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 84;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*xdimension = vdi_intout[0];
	*ydimension = vdi_intout[1];
}

/*
 * * graphic table function
 */
