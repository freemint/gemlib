/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** sets the character width in 1/65536 points (pt). The next call of 
 *  vst_height(), vst_point() or vst_arbpt32() will reset the character width. If 
 *  the width is negative the characters will be mirrored along the y-axis.
 *
 *  @param handle Device handle
 *  @param point relative width in 1/65536 points
 *  @param wchar selected character width
 *  @param hchar selected character height
 *  @param wcell selected character cell width
 *  @param hcell selected character cell height
 *
 *  @return selected width in 1/65536 points
 *
 *  @since NVDI 3.00
 *
 */

long
vst_setsize32 (short handle, long point, short *wchar, short *hchar,
               short *wcell, short *hcell)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[4]; 
	VDI_PARAMS(vdi_control, (short*)&point, 0L, vdi_intout, vdi_ptsout);
#else
	*(long*)&vdi_intin[0] = point;
#endif

	VDI_TRAP (vdi_params, handle, 252, 0,2);

	*wchar = vdi_ptsout[0];
	*hchar = vdi_ptsout[1];
	*wcell = vdi_ptsout[2];
	*hcell = vdi_ptsout[3];
	
	return vdi_intout_long(0);
}
