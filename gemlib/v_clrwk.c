#include "gem_vdiP.h"


void
v_clrwk (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 3);
}
