/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** In contrast to v_copies() this function sets the number of 
 *  copies additional to the "original" page.
 *
 *  @param handle Device handle
 *  @param times number of additional copies
 *
 *  @since depends on the driver
 *
 *  @note 
 *  Not every printer driver supports this call and since it has no return 
 *  values, you cannot inquire if it exists. Use v_copies()...
 *
 */

void
v_escape2000 (short handle, short times)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&times,                      /* vdi_intin   */
		0L, 						 /* vdi_ptsin	*/
		0L, 						 /* vdi_intout  */
		0L							 /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = times;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,2000, 0,1);
}
