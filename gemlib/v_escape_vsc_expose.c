
#include "gem.h"


void
vsc_expose (int handle, int state)
{
	vdi_intin[0] = state;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 93;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * polaroid function
 */
