#include "gem_vdiP.h"


void
v_hide_c (short handle)
{
	VDI_TRAP (vdi_params, handle, 123, 0,0);
}
