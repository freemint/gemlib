#include "gem_vdiP.h"


short
vsm_choice (short handle, short *choice)
{
	VDI_TRAP_00 (vdi_params, handle, 30);
	
	*choice = vdi_intout[0];
	
	return vdi_control[4];
}
