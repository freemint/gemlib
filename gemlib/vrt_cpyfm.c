
#include "gem.h"


void
vrt_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst,
	   short color[])
{
	vdi_intin[0] = mode;
	vdi_intin[1] = color[0];
	vdi_intin[2] = color[1];

	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	vdi_control[0] = 121;
	vdi_control[1] = 4;
	vdi_control[3] = 3;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.ptsin = pxy;

	vdi (&vdi_params);

	vdi_params.ptsin = vdi_ptsin;
}
