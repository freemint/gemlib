#include "gem_vdiP.h"


void
v_updwk (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 4);
}
