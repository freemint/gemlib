
#include "gem.h"


int
vqt_name (int handle, int element, char *name)
{
	vdi_intin[0] = element;
	vdi_control[0] = 130;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	vdi_array2str (vdi_intout + 1, name, 33);
	return vdi_intout[0];
}
