#include "gem_vdiP.h"

/** Use v_copies() to set the number of copies of a page. If \p count is 
 *  -1, the number of copies is returned.
 *
 *  @param handle Device handle
 *  @param count number of copies (including the "original one"), or -1.
 *
 *  @return number of copies (including the "original one")
 *
 *  @since depends on the driver
 *
 *  @note if the driver doesn't provide such feature, this function return 1.
 *
 *
 */

short
v_copies (short handle, short count)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 

	VDI_PARAMS(vdi_control, &count, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,28, 0,1);
	
	if (vdi_control[4]) /* function supported */
		return vdi_intout[0];
	
	/* function not supported by the driver */
	return 1;
}
