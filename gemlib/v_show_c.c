#include "gem_vdiP.h"


void
v_show_c (short handle, short reset)
{
	vdi_intin[0] = reset;
	
	VDI_TRAP (vdi_params, handle, 122, 0,1);
}
