#include "gem_vdiP.h"


void
v_pieslice (short handle,
            short x, short y, short radius, short begang, short endang)
{
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = 0;
	vdi_ptsin[5] = 0;
	vdi_ptsin[6] = radius;
	vdi_ptsin[7] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 11,3, 4,2);
}
