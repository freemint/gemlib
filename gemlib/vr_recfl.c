/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draw a filled rectangle (without outline).
 *
 *  @param handle Device handle
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
vr_recfl (short handle, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP (vdi_params, handle, 114, 2,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}

