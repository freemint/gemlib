/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_dspcur (short handle, short x, short y)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,18, 1,0);
}
