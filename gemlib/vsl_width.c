/*
 *   line attribute
 */

#include "gem_vdiP.h"


short
vsl_width (short handle, short width)
{
	vdi_ptsin[0] = width;
	vdi_ptsin[1] = 0;

	VDI_TRAP (vdi_params, handle, 16, 1,0);

	return vdi_ptsout[0];
}
