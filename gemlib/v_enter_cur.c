/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function enables text mode. The screen is cleared and the text
 *  cursor is displayed in the upper left cell of the screen.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_enter_cur (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L, 						 /* vdi_intin	*/
		0L, 						 /* vdi_ptsin	*/
		0L, 						 /* vdi_intout  */
		0L							 /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,3, 0,0);
}
