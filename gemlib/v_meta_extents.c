/*
 *   metafile funkcion
 */

#include "gem_vdiP.h"


void
v_meta_extents (short handle,
                short min_x, short min_y, short max_x, short max_y)
{
	vdi_ptsin[0] = min_x;
	vdi_ptsin[1] = min_y;
	vdi_ptsin[2] = max_x;
	vdi_ptsin[3] = max_y;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,98, 2,0);
}
