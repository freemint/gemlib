/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


short
vq_page_name (short handle, short page_id, const char *page_name,
              long *page_width, long *page_height)
{
	vdi_intin[0]                      = page_id;
	*((const char **)(&vdi_intin[1])) = page_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,38, 0,3);
	
	*page_width  = *((long*)(&vdi_intout[1]));
	*page_height = *((long*)(&vdi_intout[3]));
	
	return vdi_intout[0];
}
