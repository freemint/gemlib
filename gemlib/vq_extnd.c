#include "gem_vdiP.h"


void
vq_extnd (short handle, short flag, short work_out[])
{
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	vdi_intin[0] = flag;
	
	VDI_TRAP (vdi_params, handle, 102, 0,1);

	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;
}
