#include "gem_vdiP.h"


void
vqf_attributes (short handle, short attrib[])
{
	VDI_TRAP_00 (vdi_params, handle, 37);
	
	*(long*)(attrib)    = *(long*)(vdi_intout);
	*(long*)(attrib +2) = *(long*)(vdi_intout +2);
}
