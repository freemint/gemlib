/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vst_setsize (short handle, short point,
             short *wchar, short *hchar, short *wcell, short *hcell)
{
	vdi_intin[0] = point;
	
	VDI_TRAP (vdi_params, handle, 252, 0,1);

	*wchar = vdi_ptsout[0];
	*hchar = vdi_ptsout[1];
	*wcell = vdi_ptsout[2];
	*hcell = vdi_ptsout[3];
	
	return vdi_intout[0];
}
