
#include "gemx.h"


void
vst_track_offset (int handle, long offset, int pairmode, int *tracks,
		  int *pairs)
{
	vdi_intin[0] = 255;
	vdi_intin[1] = pairmode;
	*((long *) (&vdi_intin[2])) = offset;
	vdi_control[0] = 237;
	vdi_control[1] = 0;
	vdi_control[3] = 4;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*tracks = vdi_intout[0];
	*pairs = vdi_intout[1];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
