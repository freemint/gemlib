
#include "gem.h"


void
v_circle (short handle, short x, short y, short radius)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	vdi_ptsin[2] = 0;
	vdi_ptsin[3] = 0;
	vdi_ptsin[4] = radius;
	vdi_ptsin[5] = 0;

	vdi_control[0] = 11;
	vdi_control[1] = 3;
	vdi_control[3] = 0;
	vdi_control[5] = 4;
	vdi_control[6] = handle;

	vdi (&vdi_params);
}
