#include "gem_vdiP.h"


void
vqt_extent16 (short handle, const short *wstr, short extent[])
{
	register short n = vdi_wstrlen (wstr);
	
	vdi_params.intin  = wstr;
	vdi_params.ptsout = extent;
	
	VDI_TRAP (vdi_params, handle, 116, 0,n);

	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
}
