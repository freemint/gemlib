/*
 *  graphic table function
 */

#include "gem_vdiP.h"


void
vt_alignment (short handle, short dx, short dy)
{
	vdi_intin[0] = dx;
	vdi_intin[1] = dy;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,85, 0,2);
}
