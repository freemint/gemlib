#include "gem_vdiP.h"


void
v_gtext16n (short handle, PXY pos, const short *wstr, short num)
{
	vdi_params.intin = wstr;
	
	*(PXY*)vdi_ptsin = pos;

	VDI_TRAP (vdi_params, handle, 8, 1,num);

	vdi_params.intin = vdi_intin;
}

