/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** draws an unfilled rectangle with rounded corners
 *
 *  @param handle Device handle
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
v_rbox (short handle, short pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		pxy,                         /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_params.ptsin = pxy;
#endif

	VDI_TRAP_ESC (vdi_params, handle, 11,8, 2,0);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsin = vdi_ptsin;
#endif
}
