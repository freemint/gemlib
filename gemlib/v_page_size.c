/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the requested page size (if the page size is defined). 
 *  If the requested size does not exist, the default setting will be used.
 *
 *  @param handle Device handle
 *  @param page_id requested page size as follow:
 *         - 0:  PAGE_DEFAULT
 *         - 1:  PAGE_A3, DIN A3
 *         - 2:  PAGE_A4, DIN A4
 *         - 3:  PAGE_A5, DIN A5
 *         - 4:  PAGE_B5, DIN B5
 *         - 16: PAGE_LETTER, Letter size
 *         - 17: PAGE_HALF, Half size
 *         - 18: PAGE_LEGAL, Legal size
 *         - 19: PAGE_DOUBLE, Double size
 *         - 20: PAGE_BROAD, Broad sheet size
 *
 *  @return (-1) : error (not enough memory) =>  close the driver \n
 *          else \p page_size
 *
 *  @since depends on the driver. If the driver doesn't support this function,
 *         0 will be returned.
 *
 *  If the return value is -1, you have to close the driver because 
 *  there is not enough memory.
 *  
 */

short
v_page_size (short handle, short page_id)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, &page_id, 0L, vdi_intout, vdi_dummy );
		
	VDI_TRAP_ESC (vdi_params, handle, 5,37, 0,1);
	
	if (vdi_control[4]) /* function supported */
		return vdi_intout[0];
	
	/* the driver doesn't support this function */
	return 0;
}
