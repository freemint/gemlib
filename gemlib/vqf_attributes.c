/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** reports back the current attributes for filled objects.
 *
 *  @param handle Device handle
 *  @param attrib point to a 5-shorts array which will contain:
 *         - attrib[0]           fill type
 *         - attrib[1]           fill color
 *         - attrib[2]           fill style index
 *         - attrib[3]           writing mode
 *         - attrib[4]           perimeter flag
 *
 *  @since all VDI versions
 *
 */

void
vqf_attributes (short handle, short attrib[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		attrib,                      /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_params.intout = attrib;
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 37);
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intout = vdi_intout;
#endif
}
