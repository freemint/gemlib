/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** see v_ftext()
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param wstr string (16 bits per character)
 *
 *
 *
 */

void
v_ftext16 (short handle, short x, short y, const WCHAR * wstr)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
#endif
	register short n = vdi_wstrlen ((const short *)wstr);
#if USE_LOCAL_VDIPB
	VDI_PARAMS(vdi_control, (const short *)wstr, vdi_ptsin, vdi_dummy, vdi_dummy);
#endif
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = (const short *)wstr;
#endif
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 241, 1,n);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif
}
