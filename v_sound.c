#include "gem_vdiP.h"

/** This escape plays a sound with the given frequency and duration
 *
 *  @param handle Device handle
 *  @param freq tone frequency in hertz
 *  @param duration tone length im timer ticks
 *
 *  @since PC-GEM >= 2.00
 *
 *
 */

void
v_sound (short handle, short freq, short duration)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
		
	vdi_intin[0] = freq;
	vdi_intin[1] = duration;

	VDI_TRAP_ESC (vdi_params, handle, 5,61, 0,2);
}
