#include "gem_vdiP.h"


void
vqt_extent16n (short handle, const short *wstr, short num, short extent[])
{
	vdi_params.intin  = wstr;
	vdi_params.ptsout = extent;
	
	VDI_TRAP (vdi_params, handle, 116, 0,num);

	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
}
