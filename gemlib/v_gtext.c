#include "gem_vdiP.h"


void
v_gtext (short handle, short x, short y, const char *str)
{
	register short n = vdi_str2array (str, vdi_intin);
	vdi_ptsin[0]     = x;
	vdi_ptsin[1]     = y;
	
	VDI_TRAP (vdi_params, handle, 8, 1,n);
}
