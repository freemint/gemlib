
#include "gem.h"


int
v_copies (int handle, int count)
{
	vdi_intin[0] = count;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 28;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * special graphic funkcion
 */
