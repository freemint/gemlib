/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param xorigin 
 *  @param yorigin 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vt_origin (short handle, short xorigin, short yorigin)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; /* from TOS.HYP binding.... */
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	vdi_intin[0] = xorigin;
	vdi_intin[1] = yorigin;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,83, 0,2);
}
