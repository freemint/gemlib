/*
 *   polaroid function
 */

#include "gem_vdiP.h"


void
vsc_expose (short handle, short state)
{
	vdi_intin[0] = state;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,93, 0,1);
}
