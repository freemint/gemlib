
#include "gemx.h"


long
vq_ctab_id (int handle)
{
	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return (*(long *) &vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
