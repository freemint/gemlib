#include "gem_vdiP.h"


void
v_gtext16 (short handle, short x, short y, const short *wstr)
{
	register short n = vdi_wstrlen (wstr);
	
	vdi_params.intin = wstr;
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 8, 1,n);

	vdi_params.intin = vdi_intin;
}

