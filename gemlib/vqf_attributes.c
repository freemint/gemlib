#include "gem_vdiP.h"


void
vqf_attributes (short handle, short attrib[])
{
	VDI_TRAP (vdi_params, handle, 37, 0,0);
	
	*(long*)(attrib)    = *(long*)(vdi_intout);
	*(long*)(attrib +2) = *(long*)(vdi_intout +2);
}
