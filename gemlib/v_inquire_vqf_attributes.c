
#include "gem.h"


void
vqf_attributes (int handle, int atrib[])
{
	vdi_control[0] = 37;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	atrib[0] = vdi_intout[0];
	atrib[1] = vdi_intout[1];
	atrib[2] = vdi_intout[2];
	atrib[3] = vdi_intout[3];
}
