
#include "gemx.h"


long
vst_setsize32 (short handle, long point, short *wchar, short *hchar,
	       short *wcell, short *hcell)
{
	*((long *) (&vdi_intin[0])) = point;
	vdi_control[0] = 252;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*wchar = vdi_ptsout[0];
	*hchar = vdi_ptsout[1];
	*wcell = vdi_ptsout[2];
	*hcell = vdi_ptsout[3];
	return *((long *) (&vdi_intout[0]));
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
