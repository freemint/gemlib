/*
 *   marker attribute
 */

#include "gem_vdiP.h"


short
vsm_height (short handle, short height)
{
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	VDI_TRAP (vdi_params, handle, 19, 1,0);

	return vdi_intout[0];
}
