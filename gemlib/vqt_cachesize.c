#include "gem_vdiP.h"


void
vqt_cachesize (short handle, short which_cache, long *size)
{
	vdi_intin[0] = which_cache;
	
	VDI_TRAP (vdi_params, handle, 255, 0,1);
	
	*size = vdi_intout_long(0);
}
