/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape allows the selection of the
 *  palette on the IBM (Tm) medium-resolution color
 *  screen.
 *
 *  @param handle Device handle
 *  @param palette Color selection :
 *         - 0 = use red, green, brown palette (default)
 *         - 1 = use cyan, magenta, white palette
 *
 *  @return Palette selected
 *
 *  @since all VDI versions
 *
 *
 */

short
vs_palette (short handle, short palette)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &palette, 0L, vdi_intout, vdi_dummy );
#else
	vdi_intin[0] = palette;
#endif
		
	VDI_TRAP_ESC (vdi_params, handle, 5,60, 0,1);
	
	return vdi_intout[0];
}
