#include "gem_vdiP.h"

/** returns the number of the function key pressed
 *
 *  @param handle Device handle
 *  @param cin initialisierende Taste (0)
 *  @param cout ausgew„hlte Funktionstaste
 *
 *  @since all VDI versions
 */


void
vrq_choice (short handle, short cin, short *cout)
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, &cin, 0L, cout, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 30, 0,1);
}
