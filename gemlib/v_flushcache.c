#include "gem_vdiP.h"


short
v_flushcache (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 251);
	
	return vdi_intout[0];
}
