
#include "gem.h"


void
v_opnwk (short work_in[], short *handle, short work_out[])
{
	vdi_control[0] = 1;
	vdi_control[1] = 0;
	vdi_control[3] = 11;
	vdi_control[5] = 0;
	vdi_control[6] = 0;

	vdi_params.intin = work_in;
	vdi_params.intout = work_out;
	vdi_params.ptsout = &work_out[45];

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;
	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;

	*handle = vdi_control[6];
}

