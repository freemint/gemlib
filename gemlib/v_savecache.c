
#include "gem.h"


int
v_savecache (int handle, const char *filename)
{
	short i;

	i = vdi_str2array (filename, vdi_intin);
	vdi_control[0] = 249;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}
