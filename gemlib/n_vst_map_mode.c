/*
 *   NOTE: requires NVDI version 4.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vst_map_mode (short handle, short mode)
{
	vdi_intin[0] = mode;
	vdi_intin[1] = 1;

	VDI_TRAP (vdi_params, handle, 236, 0,2);

	return vdi_intout[0];
}
