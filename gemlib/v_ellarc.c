/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draw an elliptical arc, whose start and end angle can be set
 *  in tenths of degrees from 0 to 3600.
 *
 *  @param handle Device handle
 *  @param x x-coordinate of center point of arc
 *  @param y y-coordinate of center point of arc
 *  @param xrad Radius of X-axis
 *  @param yrad Radius of Y-axis
 *  @param begang start angle (in tenths of
 *	       degrees 0-3600), counterclockwise.
 *  @param endang end angle(in tenths of degrees
 *	       0-3600).
 *
 *  @since all VDI versions
 *
 */

void
v_ellarc (short handle, short x, short y,
          short xrad, short yrad, short begang, short endang)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_ptsin[4];   

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy);
	
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = xrad;
	vdi_ptsin[3] = yrad;

	VDI_TRAP_ESC (vdi_params, handle, 11,6, 2,2);
}
