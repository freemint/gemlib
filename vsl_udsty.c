#include "gem_vdiP.h"

/** set the pattern for the user-defined line type
 *
 *  @param handle Device handle
 *  @param pat user-defined line pattern specified in this 16-bit word.
 *         The Most Significant Bit (MSB) of the pattern
 *		   word is the first pixel in the line. This line
 *		   style is used for subsequent polyline
 *		   operations when the application selects user
 *		   defined line style, index 7.
 *
 *  @since all VDI versions
 *
 */

void
vsl_udsty (short handle, short pat)
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, &pat, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP (vdi_params, handle, 113, 0,1);
}
