#include "gem_vdiP.h"


short
v_flushcache (short handle)
{
	VDI_TRAP (vdi_params, handle, 251, 0,0);
	
	return vdi_intout[0];
}
