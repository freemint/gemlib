/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
v_page_size (short handle, short page_id)
{
	vdi_intin[0] = page_id;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,37, 0,1);
	
	return vdi_intout[0];
}
