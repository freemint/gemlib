/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws markers
 *
 *  @param handle Device handle
 *  @param count 
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
v_pmarker (short handle, short count, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP (vdi_params, handle, 7, count,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}
