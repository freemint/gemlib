
#include "gemx.h"


short
v_ctab_vdi2idx (short handle, short vdi_index)
{
	vdi_intin[0] = vdi_index;

	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 4;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
