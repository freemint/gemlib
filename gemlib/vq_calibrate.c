/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vq_calibrate (short handle, short *flag)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,77, 0,0);

	*flag = vdi_intout[0];
	
	return vdi_control[4];
}
