#include "gem_vdiP.h"


void
v_contourfill (short handle, short x, short y, short index)
{
	vdi_intin[0] = index;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP (vdi_params, handle, 103, 1,1);
}
