#include "gem_vdiP.h"


void
v_clrwk (short handle)
{
	VDI_TRAP (vdi_params, handle, 3, 0,0);
}
