
#include "gemx.h"


void
v_bez_off (int handle)
{
	vdi_control[0] = 11;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 13;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * NOTE: requires NVDI version 2.x or higher
 */
