
#include "gem.h"


void
v_output_window (int handle, int *pxyarray)
{
	vdi_ptsin[0] = pxyarray[0];
	vdi_ptsin[1] = pxyarray[1];
	vdi_ptsin[2] = pxyarray[2];
	vdi_ptsin[3] = pxyarray[3];
	vdi_control[0] = 5;
	vdi_control[1] = 2;
	vdi_control[3] = 0;
	vdi_control[5] = 21;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * special graphic funkcion
 */
