#include "gem_vdiP.h"


void
v_opnvwk (short work_in[], short *handle, short work_out[])
{
	vdi_params.intin  = &work_in[0];
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	VDI_TRAP (vdi_params, *handle, 100, 0,11);

	vdi_params.intin  = vdi_intin;
	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;

	*handle = vdi_control[6];
}

