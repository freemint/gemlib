/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** reports back the current marker attributes
 *
 *  @param handle Device handle
 *  @param attrib 
 *         - attrib[0]           marker type
 *         - attrib[1]           marker color
 *         - attrib[2]           writing mode
 *         - attrib[3]           marker height
 *         - attrib[4]           marker width
 *
 *  @since all VDI versions
 *
 */

void
vqm_attributes (short handle, short attrib[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, attrib, &attrib[3] );
	
	VDI_TRAP_00 (vdi_params, handle, 36);
}
