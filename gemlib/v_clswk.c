#include "gem_vdiP.h"


void
v_clswk (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 2);
}
