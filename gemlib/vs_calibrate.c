/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vs_calibrate (short handle, short flag, short *rgb)
{
	*((short**)(&vdi_intin[0])) = rgb;
	vdi_intin[2]                = flag;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,76, 0,3);
	
	return vdi_intout[0];
}
