#include "gem_vdiP.h"


short
v_savecache (short handle, const char *filename)
{
	register short n = vdi_str2array (filename, vdi_intin);
	
	VDI_TRAP (vdi_params, handle, 249, 0,n);
	
	return vdi_intout[0];
}
