#include "gem_vdiP.h"


short
vst_load_fonts (short handle, short select)
{
	vdi_intin[0] = select;
	
	VDI_TRAP (vdi_params, handle, 119, 0,1);
	
	return vdi_intout[0];
}
