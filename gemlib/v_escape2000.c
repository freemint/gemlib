/*
 *   special funkcion
 */

#include "gem_vdiP.h"


void
v_escape2000 (short handle, short times)
{
	vdi_intin[0] = times;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,2000, 0,1);
}
