#include "gem_vdiP.h"


short
vqt_width (short handle, short chr, short *cw, short *ldelta, short *rdelta)
{
	vdi_intin[0] = chr;

	VDI_TRAP (vdi_params, handle, 117, 0,1);

	*cw     = vdi_ptsout[0];
	*ldelta = vdi_ptsout[2];
	*rdelta = vdi_ptsout[4];
	
	return vdi_intout[0];
}
