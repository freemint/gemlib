/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_rmcur (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,19, 0,0);
}
