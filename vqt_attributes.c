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
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, &attrib[0], &attrib[6] );
	
	VDI_TRAP_00 (vdi_params, handle, 38);
}
