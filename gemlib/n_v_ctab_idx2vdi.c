
#include "gemx.h"


short
v_ctab_idx2vdi (short handle, short index)
{
	vdi_intin[0] = index;
	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 3;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
