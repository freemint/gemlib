
#include "gemx.h"


void
vst_kern (int handle, int tmode, int pmode, int *tracks, int *pairs)
{
	vdi_intin[0] = tmode;
	vdi_intin[1] = pmode;
	vdi_control[0] = 237;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*tracks = vdi_intout[0];
	*pairs = vdi_intout[1];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
