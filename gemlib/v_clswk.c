#include "gem_vdiP.h"


void
v_clswk (short handle)
{
	VDI_TRAP (vdi_params, handle, 2, 0,0);
}
