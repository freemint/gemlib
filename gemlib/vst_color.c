/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_color (short handle, short index)
{
	vdi_intin[0] = index;

	VDI_TRAP (vdi_params, handle, 22, 0,1);

	return vdi_intout[0];
}
