
#include "gem.h"


void
vsm_valuator (short handle, short in, short *out, short *term, short *status)
{
	vdi_intin[0] = in;
	vdi_control[0] = 29;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*out = vdi_intout[0];
	*term = vdi_intout[1];
	*status = vdi_control[4];
}
