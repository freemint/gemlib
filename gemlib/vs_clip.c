
#include "gem.h"


void
vs_clip (short handle, short clip_flag, short pxy[])
{
	vdi_intin[0] = clip_flag;

	vdi_control[0] = 129;
	vdi_control[1] = 2;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.ptsin = pxy;

	vdi (&vdi_params);

	vdi_params.ptsin = vdi_ptsin;
}
