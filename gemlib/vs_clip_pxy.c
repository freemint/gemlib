#include "gem_vdiP.h"


void
vs_clip_pxy (short handle, PXY pxy[])
{
	vdi_intin[0]         = 1;
	((PXY*)vdi_ptsin)[0] = pxy[0];
	((PXY*)vdi_ptsin)[1] = pxy[1];

	VDI_TRAP (vdi_params, handle, 129, 2,1);
}
