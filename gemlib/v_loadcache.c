#include "gem_vdiP.h"


short
v_loadcache (short handle, const char *filename, short mode)
{
	register short n = 1 + vdi_str2array (filename, vdi_intin + 1);

	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 250, n,0);
	
	return vdi_intout[0];
}

