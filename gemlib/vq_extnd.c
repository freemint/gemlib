
#include "gem.h"


void
vq_extnd (short handle, short flag, short work_out[])
{
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	vdi_intin[0] = flag;
	vdi_control[0] = 102;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
}
