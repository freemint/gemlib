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
	VDI_PARAMS(vdi_control, &index, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = index;
#endif
	
	VDI_TRAP (vdi_params, handle, 17, 0,1);

	return vdi_intout[0];
}
