
#include "gem.h"


void
vro_cpyfm (short handle, short mode, short pxyarray[], MFDB * src, MFDB * dst)
{
	register short i;

	for (i = 0; i < 8; i++)
		vdi_ptsin[i] = pxyarray[i];

	vdi_intin[0] = mode;
	*((MFDB **) (&vdi_control[7])) = src;
	*((MFDB **) (&vdi_control[9])) = dst;

	vdi_control[0] = 109;
	vdi_control[1] = 4;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
