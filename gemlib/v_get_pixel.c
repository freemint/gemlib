
#include "gem.h"


void
v_get_pixel (short handle, short x, short y, short *pel, short *index)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	vdi_control[0] = 105;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*pel = vdi_intout[0];
	*index = vdi_intout[1];
}
