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
	short vdi_intout[3]; 
	short vdi_ptsout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 36);

	attrib[0] = vdi_intout[0];
	attrib[1] = vdi_intout[1];
	attrib[2] = vdi_intout[2];
	attrib[3] = vdi_ptsout[0];
	attrib[4] = vdi_ptsout[1];
}
