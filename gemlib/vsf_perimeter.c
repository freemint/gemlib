/*
 *   fill attribute
 */

#include "gem_vdiP.h"


short
vsf_perimeter (short handle, short vis)
{
	vdi_intin[0] = vis;

	VDI_TRAP (vdi_params, handle, 104, 0,1);

	return vdi_intout[0];
}
