
#include "gem.h"


void
v_clswk (short handle)
{
	vdi_control[0] = 2;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
