/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param point 
 *  @param wchar 
 *  @param hchar 
 *  @param wcell 
 *  @param hcell 
 *
 *  @return 
 *
 *  @since 
 *
 *
 *
 */

short
vst_setsize (short handle, short point,
             short *wchar, short *hchar, short *wcell, short *hcell)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[4]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&point,                      /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = point;
#endif
	
	VDI_TRAP (vdi_params, handle, 252, 0,1);

	*wchar = vdi_ptsout[0];
	*hchar = vdi_ptsout[1];
	*wcell = vdi_ptsout[2];
	*hcell = vdi_ptsout[3];
	
	return vdi_intout[0];
}
