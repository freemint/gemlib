
#include "gem.h"


void
v_meta_extents (int handle, int min_x, int min_y, int max_x, int max_y)
{
	vdi_ptsin[0] = min_x;
	vdi_ptsin[1] = min_y;
	vdi_ptsin[2] = max_x;
	vdi_ptsin[3] = max_y;
	vdi_control[0] = 5;
	vdi_control[1] = 2;
	vdi_control[3] = 0;
	vdi_control[5] = 98;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * metafile function
 */
