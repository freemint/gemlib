/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


ITAB_REF
v_create_itab (short handle, COLOR_TAB * ctab, short bits)
{
	vdi_intin_ptr(0) = ctab;
	vdi_intin    [2] = bits;
	vdi_intin    [3] = 0;
	vdi_intin    [4] = 0;

	VDI_TRAP (vdi_params, handle, 208, 0,5);

	return *(ITAB_REF*)&vdi_intout[0];
}
