
#include "gemx.h"


long
v_value2color (short handle, unsigned long value, COLOR_ENTRY * color)
{
	*(unsigned long *) &vdi_intin[0] = value;
	vdi_control[0] = 204;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	*color = *(COLOR_ENTRY *) & vdi_intout[2];
	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
