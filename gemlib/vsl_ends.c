/*
 *   line attribute
 */

#include "gem_vdiP.h"


void
vsl_ends (short handle, short begstyle, short endstyle)
{
	vdi_intin[0] = begstyle;
	vdi_intin[1] = endstyle;

	VDI_TRAP (vdi_params, handle, 108, 0,2);
}
