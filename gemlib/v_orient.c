/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
v_orient (short handle, short orientation)
{
	vdi_intin[0] = orientation;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,27, 0,1);
	
	return vdi_intout[0];
}
