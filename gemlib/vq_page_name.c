/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** can be used to determine the name of a paper format and 
 *  its physical size (height and width including the non-printable margins).
 *
 *  @param handle Device handle
 *  @param page_id paper format
 *  @param page_name pointer to the name
 *  @param page_width width in micro meters \n
 *         [option CHECK_NULLPTR] page_width may be NULL
 *  @param page_height height in micro meters \n
 *         [option CHECK_NULLPTR] page_height may be NULL
 *
 *  @return paper format or -1 (error: the paper format is not defined and its size cannot 
 *          be returned.)
 *
 *  @since depends on the driver. If the driver doesn't support this function,
 *         (-1) will be returned.
 *
 */


short
vq_page_name (short handle, short page_id, char *page_name,
              long *page_width, long *page_height)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	short vdi_intout[5]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
#endif
	
	vdi_intin    [0] = page_id;
	vdi_intin_ptr(1) = page_name;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,38, 0,3);
	
	if (vdi_control[4] == 0) /* function not supported by the driver */
		return -1;
	
#if CHECK_NULLPTR
	if (page_width)
#endif
	*page_width  = vdi_intout_long(1);
#if CHECK_NULLPTR
	if (page_height)
#endif
	*page_height = vdi_intout_long(3);
	
	return vdi_intout[0];
}
