#include "gem_vdiP.h"

/** moves
 *	the alpha cursor directly to the specified
 *	row and column address anywhere on the display
 *	surface. Addresses beyond the displayable
 *	range of the screen are set to the nearest
 *	value that is within the displayable range of
 *	the screen.
 *
 *  @param handle Device handle
 *  @param row Row number (1 to maximum number of rows)
 *  @param col Column number (1 to maximum number of columns).
 *
 *  @since all VDI versions
 *
 */

void
vs_curaddress (short handle, short row, short col)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
	
	vdi_intin[0] = row;
	vdi_intin[1] = col;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,11, 0,2);
}
