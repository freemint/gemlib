#include "gem_vdiP.h"


void
vst_unload_fonts (short handle, short select)
{
	vdi_intin[0] = select;
	
	VDI_TRAP (vdi_params, handle, 120, 0,1);
}
