#include "gem_vdiP.h"


short
vsm_choice (short handle, short *choice)
{
	VDI_TRAP (vdi_params, handle, 30, 0,0);
	
	*choice = vdi_intout[0];
	
	return vdi_control[4];
}
