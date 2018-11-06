#include "gem_vdiP.h"

/** "SAMPLE KEYBOARD STATE INFORMATION" returns the state of CONTROL, ALTERNATE 
 *  and the SHIFT key(s).
 *
 *  @param handle Device handle
 *  @param state keyboard (bit numbers):
 *         - 0: Shift right
 *         - 1: Shift left
 *         - 2: Control
 *         - 3: Alternate
 *
 *  @since all VDI versions
 *
 *  @note Use the AES event functions to inquire the keyboard state
 *
 *
 */

void
vq_key_s (short handle, short *state)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, state, vdi_dummy );
	
	VDI_TRAP_00 (vdi_params, handle, 128);
}
