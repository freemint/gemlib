
#include "gem.h"


void
v_trays (int handle, int input, int output, int *set_input, int *set_output)
{
	vdi_intin[0] = input;
	vdi_intin[1] = output;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 29;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*set_input = vdi_intout[0];
	*set_output = vdi_intout[1];
}

/*
 * * special graphic funkcion
 */

int
vq_calibrate (int handle, int *flag)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 77;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*flag = vdi_intout[0];
	return vdi_control[4];
}

/*
 * * special graphic funkcion
 */
