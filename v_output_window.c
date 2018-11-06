#include "gem_vdiP.h"

/** This escape is required only for printers.
 *  It allows the application to request that a
 *  particular rectangular window of the picture be
 *  output to the printer. This escape is similar
 *  to the Update Workstation function, except that
 *  the rectangular area must be specified.
 *
 *  @param handle Device handle
 *  @param pxy window to be output
 *
 *  @since all VDI versions
 *
 *  Note that use of this function does not always
 *  guarantee that adjacent pictures will abut.
 *  Pictures will abut with a resolution of one
 *  printer head height.
 *
 *
 */

void
v_output_window (short handle, short *pxy)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,21, 2,0);
}
