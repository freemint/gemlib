
#include "gem.h"


void
v_pmarker (short handle, short count, short pxyarray[])
{
	register short i;
	register short *pts = &vdi_ptsin[0];
	register short *pxy = &pxyarray[0];

	for (i = count; i != 0; i--)
	{
		*pts++ = *pxy++;
		*pts++ = *pxy++;
	}

	vdi_control[0] = 7;
	vdi_control[1] = count;
	vdi_control[3] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
