#include "gem_vdiP.h"


void
v_get_pixel (short handle, short x, short y, short *pel, short *index)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 105, 1,0);

	*pel   = vdi_intout[0];
	*index = vdi_intout[1];
}
