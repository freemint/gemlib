/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_delete_itab (short handle, ITAB_REF itab)
{
	*(ITAB_REF*)&vdi_intin[0] = itab;

	VDI_TRAP_ESC (vdi_params, handle, 208,1, 0,2);

	return vdi_intout[0];
}
