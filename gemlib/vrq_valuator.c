#include "gem_vdiP.h"


void
vrq_valuator (short handle, short in, short *out, short *term)
{
	vdi_intin[0] = in;
	
	VDI_TRAP (vdi_params, handle, 29, 0,1);
	
	*out  = vdi_intout[0];
	*term = vdi_intout[1];
}
