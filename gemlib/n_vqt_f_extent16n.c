/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** see vqt_f_extent()
 *
 *  @param handle Device handle
 *  @param wstr 
 *  @param num string len 
 *  @param extent 
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

void
vqt_f_extent16n (short handle, const WCHAR * wstr, short num, short extent[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		wstr,                        /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		extent                       /* vdi_ptsout  */
	};
#else
	vdi_params.intin  = (const short *)wstr;
	vdi_params.ptsout = extent;
#endif
	
	VDI_TRAP (vdi_params, handle, 240, 0,num);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
#endif
}
