#include "gem_vdiP.h"


void
vql_attributes (short handle, short attrib[])
{
	VDI_TRAP (vdi_params, handle, 35, 0,0);
	
	attrib[0] = vdi_intout[0];
	attrib[1] = vdi_intout[1];
	attrib[2] = vdi_intout[2];
	attrib[3] = vdi_ptsout[0];
	attrib[4] = vdi_intout[3];
	attrib[5] = vdi_intout[4];
}
