/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws a filled circle
 *
 *  @param handle Device handle
 *  @param x x-coordinate of center point of circle
 *  @param y y-coordinate of center point of circle
 *  @param radius radius
 *
 *  @since all VDI versions
 *
 */

void
v_circle (short handle, short x, short y, short radius)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[6];   
	VDI_PARAMS(vdi_control, 0L, vdi_ptsin, vdi_dummy, vdi_dummy);
#endif
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = radius;
	vdi_ptsin[5] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 11,4, 3,0);
}
