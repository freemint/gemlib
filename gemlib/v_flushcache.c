
#include "gem.h"


int
v_flushcache (int handle)
{
	vdi_control[0] = 251;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}
