
#include "gem.h"


void
v_gtext (int handle, int x, int y, const char *str)
{
	short i;

	i = vdi_str2array (str, vdi_intin);
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	vdi_control[0] = 8;
	vdi_control[1] = 2;
	vdi_control[3] = i;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}
