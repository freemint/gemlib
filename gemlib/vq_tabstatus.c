/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vq_tabstatus (short handle)
{
	VDI_TRAP_ESC (vdi_params, handle, 5,16, 0,0);
	
	return vdi_intout[0];
}
