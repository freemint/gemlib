/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function displays a string. The string starts at the current cursor 
 *  position.
 *
 *  @param handle Device handle
 *  @param str 
 *
 *  @since all VDI versions
 *
 */

void
v_curtext (short handle, const char *str)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
#endif
	register short n = vdi_str2array (str, vdi_intin);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,12, 0,n);
}
