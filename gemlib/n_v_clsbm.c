
#include "gemx.h"


void
v_clsbm (short handle)
{
	vdi_control[0] = 101;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * NOTE: requires EdDI version 1.x or higher
 */
