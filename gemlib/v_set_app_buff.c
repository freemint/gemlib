#include "gem_vdiP.h"


void
v_set_app_buff (short handle, void *buf_p, short size)
{
	*((void**)(&vdi_intin[0])) = buf_p;
	vdi_intin[3]               = size;
	
	VDI_TRAP_ESC (vdi_params, handle, -1,6, 0,3);
}
