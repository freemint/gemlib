/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the color index for lines
 *
 *  @param handle Device handle
 *  @param index requested line color. If the index is invalid, color index 1
 *         will be selected.
 *
 *  @return realized line color
 *
 *  @since all VDI versions
 */

short
vsl_color (short handle, short index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&index,                      /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = index;
#endif
	
	VDI_TRAP (vdi_params, handle, 17, 0,1);

	return vdi_intout[0];
}
