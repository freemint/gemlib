/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** closes a physical workstation
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  If you call v_clswk() for a printer driver and if you have not called v_updwk() 
 *  or v_clear_disp_list() before, buffered commands will be executed and sent to 
 *  the printer.
 *
 */

void
v_clswk (short handle)
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
	
	VDI_TRAP_00 (vdi_params, handle, 2);
}
