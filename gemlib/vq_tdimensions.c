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
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,84, 0,0);
	
	*xdimension = vdi_intout[0];
	*ydimension = vdi_intout[1];
}
