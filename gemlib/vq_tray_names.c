
#include "gem.h"


void
vq_tray_names (short handle, const char *input_name, const char *output_name,
	       short *input, short *output)
{
	*((const char **) (&vdi_intin[0])) = input_name;
	*((const char **) (&vdi_intin[2])) = output_name;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 4;
	vdi_control[5] = 36;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*input = vdi_intout[0];
	*output = vdi_intout[1];
}

/*
 * * special graphic funkcion
 */

short
vs_calibrate (short handle, short flag, short *rgb)
{
	*((short **) (&vdi_intin[0])) = rgb;
	vdi_intin[2] = flag;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 76;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * special graphic funkcion
 */
