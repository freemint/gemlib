#include "gem_vdiP.h"


void
vqt_extent (short handle, const char *str, short extent[])
{
	register short n = vdi_str2array (str, vdi_intin);
	
	vdi_params.ptsout = extent;
	
	VDI_TRAP (vdi_params, handle, 116, 0,n);

	vdi_params.ptsout = vdi_ptsout;
}
