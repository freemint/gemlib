/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the value of the valuator device
 *
 *  @param handle Device handle
 *  @param in Initial value
 *  @param out Output value
 *  @param term Terminator
 *
 *  @since all VDI versions
 *
 *  The initial value of the
 *  valuator is incremented or decremented until a
 *  terminating character is struck. Valuator keys
 *  are typically the up-arrow and down-arrow keys.
 *  Valuator numbers range from 1 to 100. Typical
 *  implementation of the up-arrow and down-arrow
 *  keys is as follows:
 *  - Pressing the up-arrow key adds ten to the
 *    valuator.
 *  - Pressing the down-arrow key subtracts ten
 *    from the valuator.
 *  - Pressing the up-arrow key with the Shift key
 *    adds one to the valuator.
 *  - Pressing the down-arrow key with the Shift
 *    key subtracts one from the valuator.
 *
 *  @note This function is not required and may
 *  not be available on all devices.
 *
 */

void
vrq_valuator (short handle, short in, short *out, short *term)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&in,                         /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = in;
#endif
	
	VDI_TRAP (vdi_params, handle, 29, 0,1);
	
	*out  = vdi_intout[0];
	*term = vdi_intout[1];
}
