/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param buf_p 
 *  @param size 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
v_set_app_buff (short handle, void *buf_p, short size)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#endif
	
	vdi_intin_ptr(0) = buf_p;
	vdi_intin    [2] = size;
	
	VDI_TRAP_ESC (vdi_params, handle, -1,6, 0,3);
}
