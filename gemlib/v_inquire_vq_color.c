
#include "gem.h"


int
vq_color (int handle, int index, int flag, int rgb[])
{
	vdi_intin[0] = index;
	vdi_intin[1] = flag;
	vdi_control[0] = 26;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	rgb[0] = vdi_intout[1];
	rgb[1] = vdi_intout[2];
	rgb[2] = vdi_intout[3];
	return vdi_intout[0];
}
