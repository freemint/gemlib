/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draw a filled rectangle (without outline).
 *
 *  @param handle Device handle
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
vr_recfl (short handle, short pxy[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 114, 2,0);
}

