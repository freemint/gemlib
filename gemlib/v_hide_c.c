#include "gem_vdiP.h"


void
v_hide_c (short handle)
{
	VDI_TRAP_00 (vdi_params, handle, 123);
}
