/*
 *   polaroid function
 */

#include "gem_vdiP.h"


void
vsp_film (short handle, short index, short lightness)
{
	vdi_intin[0] = index;
	vdi_intin[1] = lightness;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,91, 0,2);
}
