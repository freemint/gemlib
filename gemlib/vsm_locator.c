#include "gem_vdiP.h"


short
vsm_locator (short handle, short x, short y,
             short *xout, short *yout, short *term)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP (vdi_params, handle, 28, 1,0);
	
	*xout = vdi_ptsout[0];
	*yout = vdi_ptsout[1];
	*term = vdi_intout[0];

	return ((vdi_control[4] << 1) | vdi_control[2]);
}
