
#include "gemx.h"


short
vst_skew (short handle, short skew)
{
	vdi_intin[0] = skew;
	vdi_control[0] = 253;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
