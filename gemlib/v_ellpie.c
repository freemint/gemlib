#include "gem_vdiP.h"


void
v_ellpie (short handle, short x, short y,
          short xrad, short yrad, short begang, short endang)
{
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;

	VDI_TRAP_ESC (vdi_params, handle, 11,7, 2,2);
}
