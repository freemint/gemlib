/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vst_width (short handle, short width, short *char_width, short *char_height,
           short *cell_width, short *cell_height)
{
	vdi_ptsin[0] = width;
	
	VDI_TRAP (vdi_params, handle, 231, 1,0);
	
	*char_width  = vdi_ptsout[0];
	*char_height = vdi_ptsout[1];
	*cell_width  = vdi_ptsout[2];
	*cell_height = vdi_ptsout[3];
}
