
#include "gem.h"


void
v_clrwk (int handle)
{
	vdi_control[0] = 3;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
