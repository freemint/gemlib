
#include "gemx.h"


long
v_color2nearest (int handle, long color_space, COLOR_ENTRY * color,
		 COLOR_ENTRY * nearest_color)
{
	*(long *) &vdi_intin[0] = color_space;
	*(COLOR_ENTRY *) & vdi_intin[2] = *color;

	vdi_control[0] = 204;
	vdi_control[1] = 0;
	vdi_control[3] = 6;
	vdi_control[5] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	*nearest_color = *(COLOR_ENTRY *) & vdi_intout[2];
	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
