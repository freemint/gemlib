
#include "gem.h"


void
vr_recfl (int handle, int pxyarray[])
{
	register int i;

	for (i = 0; i < 4; i++)
		vdi_ptsin[i] = pxyarray[i];

	vdi_control[0] = 114;
	vdi_control[1] = 4;
	vdi_control[3] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
