
#include "gem.h"


void
vq_extnd (int handle, int flag, int work_out[])
{
#ifndef __MSHORT__
	register short i;
#else
	vdi_params.intout = (short *) &work_out[0];
	vdi_params.ptsout = (short *) &work_out[45];
#endif

	vdi_intin[0] = flag;
	vdi_control[0] = 102;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

#ifndef __MSHORT__
	for (i = 0; i < 45; i++)
		work_out[i] = vdi_intout[i];
	for (i = 0; i < 12; i++)
		work_out[i + 45] = vdi_ptsout[i];
#else
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
#endif
}
