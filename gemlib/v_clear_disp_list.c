#include "gem_vdiP.h"


void
v_clear_disp_list (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,22, 0,0);
}
