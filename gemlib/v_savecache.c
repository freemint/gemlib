/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param filename
 *
 *  @return 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

short
v_savecache (short handle, const char *filename)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[VDI_INTOUTMAX]; 
#endif
	register short n = vdi_str2array (filename, vdi_intin);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
#endif
	
	VDI_TRAP (vdi_params, handle, 249, 0,n);
	
	return vdi_intout[0];
}
