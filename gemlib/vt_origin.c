
#include "gem.h"


void
vt_origin (int handle, int xorigin, int yorigin)
{
	vdi_intin[0] = xorigin;
	vdi_intin[1] = yorigin;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 83;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * graphic table function
 */
