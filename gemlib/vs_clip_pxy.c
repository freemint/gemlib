/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** same as vs_clip(handle,1,pxy)
 *
 *  @param handle Device handle
 *  @param pxy same as vs_clip()
 *
 */

void
vs_clip_pxy (short handle, PXY pxy[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	static short vdi_intin[1] = {1};   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		pxy,                         /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0]         = 1;
	((PXY*)vdi_ptsin)[0] = pxy[0];
	((PXY*)vdi_ptsin)[1] = pxy[1];
#endif

	VDI_TRAP (vdi_params, handle, 129, 2,1);
}
