/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** see vqt_f_extent()
 *
 *  @param handle Device handle
 *  @param wstr 
 *  @param extent 
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

void
vqt_f_extent16 (short handle, const WCHAR * wstr, short extent[])
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
#endif
	register short n = vdi_wstrlen ((const short *)wstr);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = (const short *)wstr;
	vdi_params.ptsout = extent;
#endif

	VDI_TRAP (vdi_params, handle, 240, 0,n);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
#endif
}
