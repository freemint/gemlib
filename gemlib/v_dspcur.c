
#include "gem.h"


void
v_dspcur (short handle, short x, short y)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_control[0] = 5;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[5] = 18;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * special graphic funkcion
 */
