/*
 *   graphic table function
 */

#include "gem_vdiP.h"


void
vq_tdimensions (short handle, short *xdimension, short *ydimension)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,84, 0,0);
	
	*xdimension = vdi_intout[0];
	*ydimension = vdi_intout[1];
}
