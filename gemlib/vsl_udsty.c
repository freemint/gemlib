/*
 *   line attribute
 */

#include "gem_vdiP.h"


void
vsl_udsty (short handle, short pat)
{
	vdi_intin[0] = pat;

	VDI_TRAP (vdi_params, handle, 113, 0,1);
}
