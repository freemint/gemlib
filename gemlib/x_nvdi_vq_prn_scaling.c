
#include "gemx.h"


long
vq_prn_scaling (int handle)
{
	vdi_intin[0] = -1;
	vdi_intin[1] = -1;

	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[4] = 0;
	vdi_control[5] = 39;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	if (vdi_control[4] == 2)
		return (*(long *) vdi_intout);
	else
		return -1L;
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
