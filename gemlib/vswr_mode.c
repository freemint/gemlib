
#include "gem.h"


short
vswr_mode (short handle, short mode)
{
	vdi_intin[0] = mode;

	vdi_control[0] = 32;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * general attribute
 */
