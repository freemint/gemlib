
#include "gem.h"


short
vsm_height (short handle, short height)
{
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	vdi_control[0] = 19;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * marker attribute
 */
