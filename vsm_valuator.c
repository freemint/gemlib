/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the current value of the valuator device
 *
 *  @param handle Device handle
 *  @param in Initial value
 *  @param out New valuator value
 *  @param term Keypress, if keypress event occurred.
 *  @param status 
 *         - 0 = nothing happened
 *         - 1 = valuator changed
 *         - 2 = keypress character
 *
 *  @since all VDI versions
 *
 *  The valuator device is
 *	sampled. If the valuator has changed, GEM VDI
 *	increments or decrements the valuator value as
 *	required. If a terminating event occurs, GEM
 *	VDI returns the value. If nothing happens, GEM
 *	VDI returns no value. Valuator numbers range
 *	from 1 to 100. The suggested keys are the same
 *	as for Input Valuator, Request Mode.
 *
 *	Note: This function is not required and may
 *	not be available on all devices.
 *
 */

void
vsm_valuator (short handle, short in, short *out, short *term, short *status)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	
	VDI_PARAMS(vdi_control, &in, 0L, vdi_intout, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 29, 0,1);
	
	*out    = vdi_intout[0];
	*term   = vdi_intout[1];
	*status = vdi_control[4];
}
