/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_get_outline (short handle, short index, short x_offset, short y_offset,
               short *pts, char *flags, short max_pts)
{
	vdi_intin    [0] = index;
	vdi_intin    [1] = max_pts;
	vdi_intin_ptr(2) = pts;
	vdi_intin_ptr(4) = flags;
	vdi_intin    [6] = x_offset;
	vdi_intin    [7] = y_offset;

	VDI_TRAP_ESC (vdi_params, handle, 243,1, 0,8);

	return vdi_intout[0];
}
