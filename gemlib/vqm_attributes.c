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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, attrib, &attrib[3] );
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 36);

#if !(USE_LOCAL_VDIPB)
	attrib[0] = vdi_intout[0];
	attrib[1] = vdi_intout[1];
	attrib[2] = vdi_intout[2];
	attrib[3] = vdi_ptsout[0];
	attrib[4] = vdi_ptsout[1];
#endif
}
