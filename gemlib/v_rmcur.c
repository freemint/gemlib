/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape removes the last graphic cursor placed on the screen
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_rmcur (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, 0L, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,19, 0,0);
}
