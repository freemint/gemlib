/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param dx 
 *  @param dy 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */


void
vt_alignment (short handle, short dx, short dy)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = dx;
	vdi_intin[1] = dy;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,85, 0,2);
}
