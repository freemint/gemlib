
#include "gem.h"


int
vsin_mode (int handle, int dev, int mode)
{
	vdi_intin[0] = dev;
	vdi_intin[1] = mode;
	vdi_control[0] = 33;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}
