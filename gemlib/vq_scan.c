/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
vq_scan (short handle, short *g_slice, short *g_page,
         short *a_slice, short *a_page, short *div_fac)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,24, 0,0);
	
	*g_slice = vdi_intout[0];
	*g_page  = vdi_intout[1];
	*a_slice = vdi_intout[2];
	*a_page  = vdi_intout[3];
	*div_fac = vdi_intout[4];
}
