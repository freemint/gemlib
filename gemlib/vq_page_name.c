/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vq_page_name (short handle, short page_id, char *page_name,
              long *page_width, long *page_height)
{
	vdi_intin    [0] = page_id;
	vdi_intin_ptr(1) = page_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,38, 0,3);
	
	*page_width  = vdi_intout_long(1);
	*page_height = vdi_intout_long(3);
	
	return vdi_intout[0];
}
