#include "gem_vdiP.h"


void
vq_key_s (short handle, short *state)
{
	VDI_TRAP_00 (vdi_params, handle, 128);
	
	*state = vdi_intout[0];
}
