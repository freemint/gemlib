/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vst_charmap (short handle, short mode)
{
	vdi_intin[0] = mode;

	VDI_TRAP (vdi_params, handle, 236, 0,1);
}
