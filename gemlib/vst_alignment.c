
#include "gem.h"


void
vst_alignment (int handle, int hin, int vin, int *hout, int *vout)
{
	vdi_intin[0] = hin;
	vdi_intin[1] = vin;
	vdi_control[0] = 39;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*hout = vdi_intout[0];
	*vout = vdi_intout[1];
}

/*
 * * text attribute
 */
