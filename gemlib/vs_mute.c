/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape set/unset/return the tone mute flag
 *
 *  @param handle Device handle
 *  @param action:
 *         - (-1) inquire the mute flag
 *         - 0 clear the mute flag (sound on)
 *         - 1 set the mute flag (sound off)
 *
 *  @return the mute flag set
 *
 *  @since PC-GEM >= 2.0
 *
 *
 */

short
vs_mute (short handle, short action)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	
	VDI_PARAMS(vdi_control, &action, 0L, vdi_intout, vdi_dummy );
		
	VDI_TRAP_ESC (vdi_params, handle, 5,62, 0,1);
	
	return vdi_intout[0];
}
