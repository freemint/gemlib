
#include "gem.h"


void
vst_alignment (short handle, short hin, short vin, short *hout, short *vout)
{
	vdi_intin[0] = hin;
	vdi_intin[1] = vin;

	vdi_control[0] = 39;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*hout = vdi_intout[0];
	*vout = vdi_intout[1];
}

/*
 * * text attribute
 */
