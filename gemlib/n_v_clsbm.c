/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** closes an offscreen bitmap. If the VDI has allocated the memory
 *  for the bitmap, this call frees the memory.
 *
 *  @param handle Device handle
 *
 *  @since since EdDI 1.00
 *
 */

void
v_clsbm (short handle)
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
	
	VDI_TRAP_ESC (vdi_params, handle, 101,1, 0,0);
}
