
#include "gem.h"


void
v_opnvwk (int work_in[], int *handle, int work_out[])
{
#ifndef __MSHORT___
	register int i;

	for (i = 0; i < 11; i++)
		vdi_intin[i] = work_in[i];
#else
	vdi_params.intin = &work_in[0];
	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];
#endif

	vdi_control[0] = 100;
	vdi_control[1] = 0;
	vdi_control[3] = 11;
	vdi_control[5] = 0;
	vdi_control[6] = *handle;
	vdi (&vdi_params);

#ifndef __MSHORT___
	for (i = 0; i < 45; i++)
		work_out[i] = vdi_intout[i];
	for (i = 0; i < 12; i++)
		work_out[i + 45] = vdi_ptsout[i];
#else
	vdi_params.intin = &vdi_intin[0];
	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
#endif
	*handle = vdi_control[6];
}
