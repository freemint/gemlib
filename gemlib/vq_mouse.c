/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function returns the state of the mouse buttons and the mosue position
 *
 *  @param handle Device handle
 *  @param pstatus button status
 *  @param x 
 *  @param y 
 *
 *  @since all VDI versions
 *
 *  @note Use mt_graf_mkstate() or the event functions of the AES.
 *
 */

void
vq_mouse (short handle, short *pstatus, short *x, short *y)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsout[2]; 
	VDI_PARAMS(vdi_control, 0L, 0L, pstatus, vdi_ptsout );
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 124);
	
#if !(USE_LOCAL_VDIPB)
	*pstatus = vdi_intout[0];
#endif
	*x       = vdi_ptsout[0];
	*y       = vdi_ptsout[1];
}
