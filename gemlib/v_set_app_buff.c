#include "gem_vdiP.h"


void
v_set_app_buff (short handle, void *buf_p, short size)
{
	vdi_intin_ptr(0) = buf_p;
	vdi_intin    [2] = size;
	
	VDI_TRAP_ESC (vdi_params, handle, -1,6, 0,3);
}
