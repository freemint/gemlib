#include "gem_vdiP.h"


void
vq_mouse (short handle, short *pstatus, short *x, short *y)
{
	VDI_TRAP_00 (vdi_params, handle, 124);
	
	*pstatus = vdi_intout[0];
	*x       = vdi_ptsout[0];
	*y       = vdi_ptsout[1];
}
