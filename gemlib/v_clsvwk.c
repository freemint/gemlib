#include "gem_vdiP.h"


void
v_clsvwk (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 101);
}
