/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curtext (short handle, const char *str)
{
	register short n = vdi_str2array (str, vdi_intin);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,12, 0,n);
}
