
#include "gemx.h"


long
vq_min_color (int handle, COLOR_ENTRY * hilite_color)
{
	vdi_control[0] = 209;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	*hilite_color = *(COLOR_ENTRY *) & vdi_intout[2];
	return (*(long *) vdi_intout);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
