#include "gem_vdiP.h"


void
vsc_form (short handle, short form[])
{
	vdi_params.intin = form;

	VDI_TRAP (vdi_params, handle, 111, 0,37);

	vdi_params.intin = vdi_intin;
}
