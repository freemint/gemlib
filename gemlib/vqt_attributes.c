/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function returns the current graphic text attributes
 *
 *  @param handle Device handle
 *  @param attrib defined as follow:
 *         - attrib[0]	font id
 *         - attrib[1]	text color index
 *         - attrib[2]	text rotation in 1/10 of degrees
 *         - attrib[3]	horizontal alignment
 *         - attrib[4]	vertical alignment
 *         - attrib[5]	writing mode
 *         - attrib[6]	character width
 *         - attrib[7]	character height
 *         - attrib[8]	character cell width
 *         - attrib[9]	character cell height
 *
 *  @since all VDI versions
 *
 *  @note Some version of the ATARI-VDI return the writing mode - 1
 *
 */

void
vqt_attributes (short handle, short attrib[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&attrib[0],                  /* vdi_intout  */
		&attrib[6]                   /* vdi_ptsout  */
	};
#else
	vdi_params.intout = &attrib[0];
	vdi_params.ptsout = &attrib[6];
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 38);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;
#endif
}
