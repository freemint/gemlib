/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_effects (short handle, short effects)
{
	vdi_intin[0] = effects;

	VDI_TRAP (vdi_params, handle, 106, 0,1);

	return vdi_intout[0];
}
