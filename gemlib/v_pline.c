#include "gem_vdiP.h"


void
v_pline (short handle, short count, short pxy[])
{
	vdi_params.ptsin = pxy;

	VDI_TRAP (vdi_params, handle, 6, count,0);

	vdi_params.ptsin = vdi_ptsin;
}
