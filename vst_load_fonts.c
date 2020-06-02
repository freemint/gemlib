#include "gem_vdiP.h"

/** loads the fonts for the device specified by \p handle and returns
 *  the number of additional fonts.
 *
 *  @param handle Device handle
 *  @param select 0 (reserved)
 *
 *  @return number of additional fonts
 *
 *  @since all VDI versions
 *
 *  Before you call vst_load_fonts(), call vq_gdos() and make sure that the VDI can 
 *  load additional fonts.
 *  
 */

short
vst_load_fonts (short handle, short select)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	
	VDI_PARAMS(vdi_control, &select, 0L, vdi_intout, vdi_dummy );
		
	/* NVDI expects a FONTHDR ptr here */
	*__vdi_array_ptr(10, vdi_control) = 0;

	VDI_TRAP (vdi_params, handle, 119, 0,1);
	
	return vdi_intout[0];
}
