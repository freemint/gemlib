/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** switches the mouse cursor off
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  @note Use mt_graf_mouse() to switch the cursor on or off.
 *
 */

void
v_hide_c (short handle)
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
	
	VDI_TRAP_00 (vdi_params, handle, 123);
}
