/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vst_track_offset (short handle, long offset, short pairmode,
                  short *tracks, short *pairs)
{
	vdi_intin[0]          = 255;
	vdi_intin[1]          = pairmode;
	*(long*)&vdi_intin[2] = offset;
	
	VDI_TRAP (vdi_params, handle, 237, 0,4);
	
	*tracks = vdi_intout[0];
	*pairs  = vdi_intout[1];
}
