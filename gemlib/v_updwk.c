#include "gem_vdiP.h"


void
v_updwk (short handle)
{
	VDI_TRAP (vdi_params, handle, 4, 0,0);
}
