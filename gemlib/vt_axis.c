/*
 *  graphic table function
 */

#include "gem_vdiP.h"


void
vt_axis (short handle, short xres, short yres, short *xset, short *yset)
{
	vdi_intin[0] = xres;
	vdi_intin[1] = yres;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,82, 0,2);
	
	*xset = vdi_intout[0];
	*yset = vdi_intout[1];
}
