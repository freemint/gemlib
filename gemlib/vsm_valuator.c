#include "gem_vdiP.h"


void
vsm_valuator (short handle, short in, short *out, short *term, short *status)
{
	vdi_intin[0] = in;
	
	VDI_TRAP (vdi_params, handle, 29, 0,1);
	
	*out    = vdi_intout[0];
	*term   = vdi_intout[1];
	*status = vdi_control[4];
}
