/*
 *  $Id$
 */

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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = row;
	vdi_intin[1] = col;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,11, 0,2);
}
