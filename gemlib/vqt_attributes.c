#include "gem_vdiP.h"


void
vqt_attributes (short handle, short atrib[])
{
	vdi_params.intout = &atrib[0];
	vdi_params.ptsout = &atrib[6];

	VDI_TRAP (vdi_params, handle, 38, 0,0);

	vdi_params.intout = vdi_intout;
	vdi_params.ptsout = vdi_ptsout;
}
