
#include "gemx.h"


long
vq_px_format (int handle, unsigned long *px_format)
{
	vdi (&vdi_params);
	vdi_control[0] = 204;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 3;
	vdi_control[6] = handle;

	*px_format = *(unsigned long *) &vdi_intout[2];
	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
