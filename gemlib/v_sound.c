/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape plays a sound with the given frequency and duration
 *
 *  @param handle Device handle
 *  @param freq 
 *  @param duration 
 *
 *  @since PC-GEM >= 2.00
 *
 *
 */

void
v_sound (short handle, short freq, short duration)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
#endif
		
	vdi_intin[0] = freq;
	vdi_intin[1] = duration;

	VDI_TRAP_ESC (vdi_params, handle, 5,61, 0,2);
}
