/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws an arc, whose start and end angle can be set in tenths of 
 *  degrees from 0 to 3600.
 *
 *  @param handle Device handle
 *  @param x x-coordinate of center point of arc
 *  @param y y-coordinate of center point of arc
 *  @param radius radius
 *  @param begang start angle (in tenths of degrees 0-3600)
 *  @param endang end angle (in tenths of degrees 0-3600)
 *
 *  @since all VDI versions
 *
 */

void
v_arc (short handle, short x, short y, short radius, short begang, short endang)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_ptsin[8];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		&vdi_ptsin[0],               /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = begang;
	vdi_intin[1] = endang;
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = 0;
	vdi_ptsin[5] = 0;
	vdi_ptsin[6] = radius;
	vdi_ptsin[7] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 11,2, 4,2);
}
