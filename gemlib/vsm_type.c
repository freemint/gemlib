/*
 *   marker attribute
 */

#include "gem_vdiP.h"


short
vsm_type (short handle, short symbol)
{
	vdi_intin[0] = symbol;

	VDI_TRAP (vdi_params, handle, 18, 0,1);

	return vdi_intout[0];
}
