/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_font (short handle, short font)
{
	vdi_intin[0] = font;

	VDI_TRAP (vdi_params, handle, 21, 0,1);

	return vdi_intout[0];
}
