
#include "gem.h"


short
vsm_locator (short handle, short x, short y, short *xout, short *yout, short *term)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_control[0] = 28;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*xout = vdi_ptsout[0];
	*yout = vdi_ptsout[1];
	*term = vdi_intout[0];
	return ((vdi_control[4] << 1) | vdi_control[2]);
}
