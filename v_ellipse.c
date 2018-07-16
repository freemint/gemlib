/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param xrad 
 *  @param yrad 
 *
 *  @since all VDI versions
 *
 */

void
v_ellipse (short handle, short x, short y, short xrad, short yrad)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[4];   

	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_dummy );
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;
	
	VDI_TRAP_ESC (vdi_params, handle, 11,5, 2,0);
}
