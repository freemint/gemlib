/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the position of the mouse. You can use this function to 
 *  change the position of the mouse cursor (but you should not because it will only 
 *  irritate the user). This functions waits until a mouse button is pressed.
 *
 *  @param handle Device handle
 *  @param x new x-coordinate of the mouse cursor
 *  @param y new y-coordinate of the mouse cursor
 *  @param xout old x-coordinate of the mouse cursor
 *  @param yout old x-coordinate of the mouse cursor
 *  @param term Maustastenstatus+31
 *
 *  @since all VDI versions
 *
 */

void
vrq_locator (short handle, short x, short y,
             short *xout, short *yout, short *term)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[2]; 
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, term, vdi_ptsout );
#endif
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP (vdi_params, handle, 28, 1,0);
	
	*xout = vdi_ptsout[0];
	*yout = vdi_ptsout[1];
#if !(USE_LOCAL_VDIPB)
	*term = vdi_intout[0];
#endif
}
