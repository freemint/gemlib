/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_advance (short handle, short ch,
             short *advx, short *advy, short *xrem, short *yrem)
{
	vdi_intin[0] = ch;

	VDI_TRAP (vdi_params, handle, 247, 0,1);

	*advx = vdi_ptsout[0];
	*advy = vdi_ptsout[1];
	*xrem = vdi_ptsout[2];
	*yrem = vdi_ptsout[3];
}
