/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** closes a virtual workstation
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_clsvwk (short handle)
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
	
	VDI_TRAP_00 (vdi_params, handle, 101);
}
