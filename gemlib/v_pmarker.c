/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws markers
 *
 *  @param handle Device handle
 *  @param count 
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
v_pmarker (short handle, short count, short pxy[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 7, count,0);
}
