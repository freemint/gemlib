/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vst_kern (short handle, short tmode, short pmode, short *tracks, short *pairs)
{
	vdi_intin[0] = tmode;
	vdi_intin[1] = pmode;
	
	VDI_TRAP (vdi_params, handle, 237, 0,2);
	
	*tracks = vdi_intout[0];
	*pairs  = vdi_intout[1];
}
