#include "gem_vdiP.h"


void
v_ellipse (short handle, short x, short y, short xrad, short yrad)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;
	
	VDI_TRAP_ESC (vdi_params, handle, 11,5, 2,0);
}
