/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param str 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
v_alpha_text (short handle, const char *str)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[5]; /* from TOS.HYP */
#endif
	register short n = vdi_str2array (str, vdi_intin);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,25, 0,n);
}
