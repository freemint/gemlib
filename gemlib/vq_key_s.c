#include "gem_vdiP.h"


void
vq_key_s (short handle, short *state)
{
	VDI_TRAP (vdi_params, handle, 128, 0,0);
	
	*state = vdi_intout[0];
}
