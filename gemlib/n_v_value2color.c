/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


long
v_value2color (short handle, unsigned long value, COLOR_ENTRY * color)
{
	*(unsigned long *)&vdi_intin[0] = value;
	
	VDI_TRAP_ESC (vdi_params, handle, 204,1, 0,2);

	*color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
