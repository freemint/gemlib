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
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&font,                       /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = font;
#endif
	
	VDI_TRAP (vdi_params, handle, 21, 0,1);

	return vdi_intout[0];
}
