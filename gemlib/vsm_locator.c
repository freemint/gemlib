/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** returns the coordinates of the mouse cursor and sets new 
 *  coordinates
 *
 *  @param handle Device handle
 *  @param x new x-coordinate of the mouse cursor
 *  @param y new y-coordinate of the mouse cursor
 *  @param xout old x-coordinate of the mouse cursor
 *  @param yout old y-coordinate of the mouse cursor
 *  @param term mouse button + 31
 *
 *  @return a bitmap value:
 *          - bit 0 (0x01): mouse movement
 *          - bit 1 (0x02): button pressed
 *
 *  @since all VDI versions
 *
 */

short
vsm_locator (short handle, short x, short y,
             short *xout, short *yout, short *term)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	short vdi_ptsout[2]; 
	
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, term, vdi_ptsout );
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP (vdi_params, handle, 28, 1,0);
	
	*xout = vdi_ptsout[0];
	*yout = vdi_ptsout[1];

	return ((vdi_control[4] << 1) | vdi_control[2]);
}
