/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** "EXIT ALPHA MODE" switches back to graphics mode.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_exit_cur (short handle)
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
	
	VDI_TRAP_ESC (vdi_params, handle, 5,2, 0,0);
}
