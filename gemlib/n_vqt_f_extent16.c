/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

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
#endif
	register short n = vdi_wstrlen ((const short *)wstr);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, wstr, 0L, vdi_dummy, extent);
#endif

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
