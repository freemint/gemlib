/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param g_slice 
 *  @param g_page 
 *  @param a_slice 
 *  @param a_page 
 *  @param div_fac 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vq_scan (short handle, short *g_slice, short *g_page,
         short *a_slice, short *a_page, short *div_fac)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[5]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,24, 0,0);
	
	*g_slice = vdi_intout[0];
	*g_page  = vdi_intout[1];
	*a_slice = vdi_intout[2];
	*a_page  = vdi_intout[3];
	*div_fac = vdi_intout[4];
}
