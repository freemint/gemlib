#include "gem_vdiP.h"


void
v_clsvwk (short handle)
{
	VDI_TRAP (vdi_params, handle, 101, 0,0);
}
