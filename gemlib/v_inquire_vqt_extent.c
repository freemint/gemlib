
#include "gem.h"


void
vqt_extent (int handle, const char *str, int extent[])
{
	short i;

	i = vdi_str2array (str, vdi_intin);
	vdi_control[0] = 116;
	vdi_control[1] = 0;
	vdi_control[3] = i;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	for (i = 0; i < 8; i++)
		extent[i] = vdi_ptsout[i];
}
