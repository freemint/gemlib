
#include "gem.h"


void
v_output_window (short handle, short *pxy)
{
	vdi_control[0] = 5;
	vdi_control[1] = 2;
	vdi_control[3] = 0;
	vdi_control[5] = 21;
	vdi_control[6] = handle;

	vdi_params.ptsin = pxy;

	vdi (&vdi_params);

	vdi_params.ptsin = vdi_ptsin;
}

/*
 * * special graphic funkcion
 */
