/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** selects a font for text output
 *
 *  @param handle Device handle
 *  @param font requested font. If a font with the requested 
 *         does not exist, the system font will be chosen.
 *
 *  @return selected font
 *
 *  @since all VDI versions
 *
 */

short
vst_font (short handle, short font)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &font, 0L, vdi_intout, 0L );
#else
	vdi_intin[0] = font;
#endif
	
	VDI_TRAP (vdi_params, handle, 21, 0,1);

	return vdi_intout[0];
}
