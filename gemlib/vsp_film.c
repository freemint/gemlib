/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *  @param lightness 
 *
 *  @since all VDI versions
 *
 *  @sa
 *
 *
 *
 */

void
vsp_film (short handle, short index, short lightness)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
#endif
	
	vdi_intin[0] = index;
	vdi_intin[1] = lightness;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,91, 0,2);
}
