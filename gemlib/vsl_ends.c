/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** changes the style of the line ends 
 *
 *  @param handle Device handle
 *  @param begstyle end style for the first point
 *  @param endstyle end style for the last point \n
 *         end style should be one of the following value:
 *         -  SQUARE (0)
 *         -  ARROWED (1)
 *         -  ROUND (2)
 *
 *  @since all VDI versions
 *
 *  @note The TOS 4.04 (other versions were not investigated)
 *        requires the intout array to be set. Otherwise it
 *        crashes.
 */

void
vsl_ends (short handle, short begstyle, short endstyle)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy );
	
	vdi_intin[0] = begstyle;
	vdi_intin[1] = endstyle;

	VDI_TRAP (vdi_params, handle, 108, 0,2);
}
