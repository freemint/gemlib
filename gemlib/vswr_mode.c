
#include "gem.h"


int
vswr_mode (int handle, int mode)
{
	vdi_intin[0] = mode;

	vdi_control[0] = 32;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * general attribute
 */
