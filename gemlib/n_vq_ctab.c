/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vq_ctab (short handle, long ctab_length, COLOR_TAB * ctab)
{
	*(long*)&vdi_intin[0] = ctab_length;
	
	vdi_params.intout = (short*)ctab;
	
	VDI_TRAP (vdi_params, handle, 206, 0,2);

	vdi_params.intout = vdi_intout;

	return (vdi_control[4] ? 1 : 0);
}
