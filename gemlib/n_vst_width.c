
#include "gemx.h"


void
vst_width (short handle, short width, short *char_width, short *char_height,
	   short *cell_width, short *cell_height)
{
	vdi_ptsin[0] = width;
	vdi_control[0] = 231;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*char_width = vdi_ptsout[0];
	*char_height = vdi_ptsout[1];
	*cell_width = vdi_ptsout[2];
	*cell_height = vdi_ptsout[3];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
