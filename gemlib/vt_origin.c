/*
 *  graphic table function
 */

#include "gem_vdiP.h"


void
vt_origin (short handle, short xorigin, short yorigin)
{
	vdi_intin[0] = xorigin;
	vdi_intin[1] = yorigin;
	
	vdi (&vdi_params);
	VDI_TRAP_ESC (vdi_params, handle, 5,83, 0,2);
}
