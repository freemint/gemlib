#include "gem_vdiP.h"


void
vs_clip_off (short handle)
{
	vdi_intin[0] = 0;

	VDI_TRAP (vdi_params, handle, 129, 2,1);
}
