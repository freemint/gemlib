
#include "gem.h"


void
vro_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst)
{
	vdi_intin[0] = mode;
	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	vdi_control[0] = 109;
	vdi_control[1] = 4;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.ptsin = pxy;

	vdi (&vdi_params);

	vdi_params.ptsin = vdi_ptsin;
}
