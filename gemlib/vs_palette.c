/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vs_palette (short handle, short palette)
{
	vdi_intin[0] = palette;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,60, 0,1);
	
	return vdi_intout[0];
}
