
#include "gemx.h"


int
vst_charmap (int handle, int mode)
{
	vdi_intin[0] = mode;
	vdi_intin[1] = 1;
	vdi_control[0] = 236;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
