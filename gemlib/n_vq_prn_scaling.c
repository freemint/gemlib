/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
vq_prn_scaling (short handle)
{
	vdi_intin[0] = -1;
	vdi_intin[1] = -1;

	VDI_TRAP_ESC (vdi_params, handle, 5,39, 0,2);

	return (vdi_control[4] == 2 ? vdi_intout_long(0) : -1L);
}
