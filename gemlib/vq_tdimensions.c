/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param xdimension 
 *  @param ydimension 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vq_tdimensions (short handle, short *xdimension, short *ydimension)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,84, 0,0);
	
	*xdimension = vdi_intout[0];
	*ydimension = vdi_intout[1];
}
