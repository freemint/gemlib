#include "gem_vdiP.h"


void
v_rbox (short handle, short pxy[])
{
	vdi_params.ptsin = pxy;

	VDI_TRAP_ESC (vdi_params, handle, 11,8, 2,0);

	vdi_params.ptsin = vdi_ptsin;
}
