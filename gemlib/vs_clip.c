
#include "gem.h"


void
vs_clip (int handle, int clip_flag, int pxyarray[])
{
	register int i;

	vdi_intin[0] = clip_flag;
	for (i = 0; i < 4; i++)
		vdi_ptsin[i] = pxyarray[i];
	vdi_control[0] = 129;
	vdi_control[1] = 2;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
