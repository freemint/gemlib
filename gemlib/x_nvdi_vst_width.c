
#include "gemx.h"


void
vst_width (int handle, int width, int *char_width, int *char_height,
	   int *cell_width, int *cell_height)
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
