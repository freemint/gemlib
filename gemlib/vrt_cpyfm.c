
#include "gem.h"


void
vrt_cpyfm (short handle, short mode, short pxyarray[], MFDB * src, MFDB * dst,
	   short color[])
{
	register short i;

	for (i = 0; i < 8; i++)
		vdi_ptsin[i] = pxyarray[i];

	vdi_intin[0] = mode;
	vdi_intin[1] = color[0];
	vdi_intin[2] = color[1];

	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	vdi_control[0] = 121;
	vdi_control[1] = 4;
	vdi_control[3] = 3;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
