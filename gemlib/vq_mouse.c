
#include "gem.h"


void
vq_mouse (short handle, short *pstatus, short *x, short *y)
{
	vdi_control[0] = 124;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*pstatus = vdi_intout[0];
	*x = vdi_ptsout[0];
	*y = vdi_ptsout[1];
}
