#include "gem_vdiP.h"


void
vs_clip (short handle, short clip_flag, short pxy[])
{
	vdi_params.ptsin = pxy;

	vdi_intin[0] = clip_flag;

	VDI_TRAP (vdi_params, handle, 129, 2,1);

	vdi_params.ptsin = vdi_ptsin;
}
