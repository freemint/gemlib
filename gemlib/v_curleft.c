/*
 *   text function
 */

#include "gem_vdiP.h"


void
v_curleft (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,7, 0,0);
}
