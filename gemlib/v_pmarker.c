#include "gem_vdiP.h"


void
v_pmarker (short handle, short count, short pxy[])
{
	vdi_params.ptsin = pxy;

	VDI_TRAP (vdi_params, handle, 7, count,0);

	vdi_params.ptsin = vdi_ptsin;
}
