/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** A filled rectangle with rounded corners is drawn by this function.
 *
 *  @param handle Device handle
 *  @param pxy Koordinaten
 *
 *  @since all VDI versions
 *
 */

void
v_rfbox (short handle, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
#else
	vdi_params.ptsin = pxy;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 11,9, 2,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}

