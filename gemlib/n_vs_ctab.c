/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vs_ctab (short handle, COLOR_TAB * ctab)
{
	vdi_params.intin = (short *) ctab;

	VDI_TRAP (vdi_params, handle, 205, 0,(short)(ctab->length /2));

	vdi_params.intin = vdi_intin;

	return (vdi_intout[0]);
}
