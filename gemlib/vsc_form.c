
#include "gem.h"


void
vsc_form (short handle, short form[])
{
	vdi_params.intin = form;

	vdi_control[0] = 111;
	vdi_control[1] = 0;
	vdi_control[3] = 37;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;
}
