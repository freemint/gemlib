/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** same as v_gtext()
 *
 *  @param handle Device handle
 *  @param x 
 *  @param y 
 *  @param wstr string, with 16 bits per character.
 *
 *  @since all VDI versions
 *
 */

void
v_gtext16 (short handle, short x, short y, const short *wstr)
{
	register short n = vdi_wstrlen (wstr);
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_ptsin[2];   
	VDI_PARAMS(vdi_control, wstr, vdi_ptsin, vdi_dummy, vdi_dummy );
#endif
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = wstr;
#endif
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 8, 1,n);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif
}

