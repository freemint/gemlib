/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** see vqt_extent()
 *
 *  @param handle Device handle
 *  @param wstr string in 16-bit format (16 bits per character)
 *  @param extent coordinates of the rectangle
 *
 */

void
vqt_extent16 (short handle, const short *wstr, short extent[])
{
	register short n = vdi_wstrlen (wstr);
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS( vdi_control, wstr, 0L, 0L, extent);
#endif
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = wstr;
	vdi_params.ptsout = extent;
#endif
	
	VDI_TRAP (vdi_params, handle, 116, 0,n);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
#endif
}
