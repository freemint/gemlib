/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param mode 
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

void
vst_scratch (short handle, short mode)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
	VDI_PARAMS(vdi_control, &mode, 0L, vdi_intout, vdi_ptsout );
#else
	vdi_intin[0] = mode;
#endif
	
	VDI_TRAP (vdi_params, handle, 244, 0,1);
}
