
#include "gem.h"


void
vt_alignment (int handle, int dx, int dy)
{
	vdi_intin[0] = dx;
	vdi_intin[1] = dy;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 85;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * graphic table function
 */
