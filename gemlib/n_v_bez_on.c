
#include "gemx.h"


short
v_bez_on (short handle)
{
	vdi_control[0] = 11;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[5] = 13;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 2.x or higher
 */
