
#include "gem.h"


void
vq_key_s (int handle, int *state)
{
	vdi_control[0] = 128;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*state = vdi_intout[0];
}
