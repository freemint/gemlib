/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** sets special text effects (really?).
 *
 *  @param handle Device handle
 *  @param effects requested text effects. \p effects is one, or any combination
 *         of the following values:
 *         - TXT_NORMAL (0x0000)
 *         - TXT_THICKENED (0x0001)
 *         - TXT_LIGHT (0x0002)
 *         - TXT_SKEWED (0x0004)
 *         - TXT_UNDERLINED (0x0008)
 *         - TXT_OUTLINED (0x0010)
 *         - TXT_SHADOWED (0x0020)
 *
 *  @return selected text effects
 *
 *  @since all VDI versions
 */

short
vst_effects (short handle, short effects)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &effects, 0L, vdi_intout, 0L );
#else
	vdi_intin[0] = effects;
#endif
	
	VDI_TRAP (vdi_params, handle, 106, 0,1);

	return vdi_intout[0];
}
