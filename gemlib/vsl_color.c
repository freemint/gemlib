
#include "gem.h"


short
vsl_color (short handle, short index)
{
	vdi_intin[0] = index;
	vdi_control[0] = 17;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * line attribute
 */
