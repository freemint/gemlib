
#include "gem.h"


int
v_orient (int handle, int orientation)
{
	vdi_intin[0] = orientation;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 27;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * special graphic funkcion
 */
