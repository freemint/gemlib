#include "gem_vdiP.h"


void
vq_mouse (short handle, short *pstatus, short *x, short *y)
{
	VDI_TRAP (vdi_params, handle, 124, 0,0);
	
	*pstatus = vdi_intout[0];
	*x       = vdi_ptsout[0];
	*y       = vdi_ptsout[1];
}
