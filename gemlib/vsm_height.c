/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets the marker height
 *
 *  @param handle Device handle
 *  @param height requested marker height. If the requested height does not exist, the 
 *         next smaller height will be selected.
 *         Marker type 1 (dot) is always 1 pixel high.
 *
 *  @return realized marker height
 *
 *  @since all VDI versions
 *
 */

/* binding note: height is stored in vdi_ptsin[1], it's not an
   error (maybe you think vdi_intin[0] is a better choice) */

short
vsm_height (short handle, short height)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[2]; 
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_ptsout );
#endif
	
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	VDI_TRAP (vdi_params, handle, 19, 1,0);

	/* here, vdi_ptsout[0] contains the selected width for markers */
	
	return vdi_ptsout[1];
}
