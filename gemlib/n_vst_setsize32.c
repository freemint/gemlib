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
 *  @param wchar selected character width \n
 *         [option CHECK_NULLPTR] wchar may be NULL
 *  @param hchar selected character height \n
 *         [option CHECK_NULLPTR] hchar may be NULL
 *  @param wcell selected character cell width \n
 *         [option CHECK_NULLPTR] wcell may be NULL
 *  @param hcell selected character cell height \n
 *         [option CHECK_NULLPTR] hcell may be NULL
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
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[4]; 

	VDI_PARAMS(vdi_control, (short*)&point, 0L, vdi_intout, vdi_ptsout);

	VDI_TRAP (vdi_params, handle, 252, 0,2);

#if CHECK_NULLPTR
	if (wchar)
#endif
	*wchar = vdi_ptsout[0];
#if CHECK_NULLPTR
	if (hchar)
#endif
	*hchar = vdi_ptsout[1];
#if CHECK_NULLPTR
	if (wcell)
#endif
	*wcell = vdi_ptsout[2];
#if CHECK_NULLPTR
	if (hcell)
#endif
	*hcell = vdi_ptsout[3];
	
	return vdi_intout_long(0);
}
