
#include "gem.h"


void
vqt_attributes (short handle, short atrib[])
{
	vdi_params.intout = &atrib[0];
	vdi_params.ptsout = &atrib[6];

	vdi_control[0] = 38;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
}
