/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
v_copies (short handle, short count)
{
	vdi_intin[0] = count;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,28, 0,1);
	
	return vdi_intout[0];
}
