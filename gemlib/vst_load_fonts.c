/*
 *  $Id$
 */

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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&select,                     /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = select;
#endif
		
	VDI_TRAP (vdi_params, handle, 119, 0,1);
	
	return vdi_intout[0];
}
