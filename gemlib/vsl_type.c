/*
 *   line attribute
 */

#include "gem_vdiP.h"


short
vsl_type (short handle, short style)
{
	vdi_intin[0] = style;

	VDI_TRAP (vdi_params, handle, 15, 0,1);

	return vdi_intout[0];
}
