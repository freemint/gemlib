
#include "gem.h"


short
vq_calibrate (short handle, short *flag)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 77;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*flag = vdi_intout[0];
	return vdi_control[4];
}

/*
 * * special graphic funkcion
 */
