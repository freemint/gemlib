#include "gem_vdiP.h"


void
vr_recfl (short handle, short pxy[])
{
	vdi_params.ptsin = pxy;

	VDI_TRAP (vdi_params, handle, 114, 2,0);

	vdi_params.ptsin = vdi_ptsin;
}

