/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param which_cache 
 *  @param size 
 *
 *  @since 
 *
 */

void
vqt_cachesize (short handle, short which_cache, long *size)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; /* todo (doc wanted) */
	short vdi_ptsout[VDI_PTSOUTMAX]; /* todo (doc wanted) */

	VDI_PARAMS(vdi_control, &which_cache, 0L, vdi_intout, vdi_ptsout );
	
	VDI_TRAP (vdi_params, handle, 255, 0,1);
	
	*size = vdi_intout_long(0);
}
