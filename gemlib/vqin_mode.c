
#include "gem.h"


void
vqin_mode (short handle, short dev, short *mode)
{
	vdi_intin[0] = dev;
	vdi_control[0] = 115;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*mode = vdi_intout[0];
}
