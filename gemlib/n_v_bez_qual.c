
#include "gemx.h"


void
v_bez_qual (short handle, short percent, short *actual)
{
	vdi_intin[0] = 32;
	vdi_intin[1] = 1;
	vdi_intin[2] = percent;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 99;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*actual = vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 2.x or higher
 */
