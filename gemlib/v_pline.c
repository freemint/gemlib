/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** connects all points in \p pxy with lines
 *
 *  @param handle Device handle
 *  @param count 
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
v_pline (short handle, short count, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, pxy, 0L, 0L );
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP (vdi_params, handle, 6, count,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}
