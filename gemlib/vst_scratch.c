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
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; /* todo (doc wanted) */
	short vdi_ptsout[VDI_PTSOUTMAX]; /* todo (doc wanted) */
	
	VDI_PARAMS(vdi_control, &mode, 0L, vdi_intout, vdi_ptsout );
	
	VDI_TRAP (vdi_params, handle, 244, 0,1);
}
