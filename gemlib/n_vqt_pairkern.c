/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_pairkern (short handle, short ch1, short ch2, long *x, long *y)
{
	vdi_intin[0] = ch1;
	vdi_intin[1] = ch2;
	
	VDI_TRAP (vdi_params, handle, 235, 0,2);
	
	*x = *(long*)&vdi_ptsout[0];
	*y = *(long*)&vdi_ptsout[2];
}
