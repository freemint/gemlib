/*
 *   line attribute
 */

#include "gem_vdiP.h"


short
vsl_color (short handle, short index)
{
	vdi_intin[0] = index;

	VDI_TRAP (vdi_params, handle, 17, 0,1);

	return vdi_intout[0];
}
