/*
 *   NOTE: requires NVDI version 2.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_bez_qual (short handle, short percent, short *actual)
{
	vdi_intin[0] = 32;
	vdi_intin[1] = 1;
	vdi_intin[2] = percent;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,3);
	
	*actual = vdi_intout[0];
}
