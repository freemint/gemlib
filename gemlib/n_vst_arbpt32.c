/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** Similar to vst_point() this function sets the character height in points, but 
 *  you are able to change the size in steps of 1/65536 points. If you request a 
 *  negative height, the characters are mirrored along the x-axis.
 *
 *  @param handle Device handle
 *  @param point requested height in 1/65536 pts
 *  @param wchar selected character width
 *  @param hchar selected character height
 *  @param wcell selected character cell width
 *  @param hcell selected character cell height
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
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	short vdi_ptsout[4]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		(short*)&point,              /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#else
	*(long*)&vdi_intin[0] = point;
#endif
	
	VDI_TRAP (vdi_params, handle, 246, 0,2);

	*wchar = vdi_ptsout[0];
	*hchar = vdi_ptsout[1];
	*wcell = vdi_ptsout[2];
	*hcell = vdi_ptsout[3];
	
	return vdi_intout_long(0);
}
