
#include "gem.h"


void
v_fillarea (short handle, short count, short pxy[])
{
	vdi_control[0] = 9;
	vdi_control[1] = count;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.ptsin = pxy;

	vdi (&vdi_params);

	vdi_params.ptsin = vdi_ptsin;
}
