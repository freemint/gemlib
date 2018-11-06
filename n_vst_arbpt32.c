#include "gem_vdiP.h"
#include "mt_gemx.h"

/** Similar to vst_point() this function sets the character height in points, but 
 *  you are able to change the size in steps of 1/65536 points. If you request a 
 *  negative height, the characters are mirrored along the x-axis.
 *
 *  @param handle Device handle
 *  @param point requested height in 1/65536 pts
 *  @param wchar selected character width \n
 *         [option CHECK_NULLPTR] wchar may be NULL
 *  @param hchar selected character height \n
 *         [option CHECK_NULLPTR] hchar may be NULL
 *  @param wcell selected character cell width \n
 *         [option CHECK_NULLPTR] wcell may be NULL
 *  @param hcell selected character cell height \n
 *         [option CHECK_NULLPTR] hcell may be NULL
 *
 *  @return selected height in 1/65536 pts
 *
 *  @since NVDI 3.00
 *
 *  @note
 *  The returned character widths are rounded values which cannot be used for 
 *  precise character placement.
 *  
 *
 */

long
vst_arbpt32 (short handle, long point,
             short *wchar, short *hchar, short *wcell, short *hcell)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[4]; 

	VDI_PARAMS(vdi_control, (short*)&point, 0L, vdi_intout, vdi_ptsout);
	vdi_intout_long(0) = 0;
	
	VDI_TRAP (vdi_params, handle, 246, 0,2);

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
	
	if (vdi_control[4] >= 2)
		return vdi_intout_long(0);
	return 0;
}
