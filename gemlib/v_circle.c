#include "gem_vdiP.h"


void
v_circle (short handle, short x, short y, short radius)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = radius;
	vdi_ptsin[5] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 11,4, 3,0);
}
