/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** fills an area which is limited by another color or the edges of 
 *  the display. Use this function on the screen only!
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param index color index
 *
 *  @since all VDI versions
 *
 */

void
v_contourfill (short handle, short x, short y, short index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	VDI_PARAMS(vdi_control, &index, vdi_ptsin, 0L, 0L);
#else
	vdi_intin[0] = index;
#endif
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP (vdi_params, handle, 103, 1,1);
}
