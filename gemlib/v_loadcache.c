
#include "gem.h"


short
v_loadcache (short handle, const char *filename, short mode)
{
	short i;

	vdi_intin[0] = mode;
	i = vdi_str2array (filename, vdi_intin + 1);
	vdi_control[0] = 250;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}
