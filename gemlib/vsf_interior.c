
#include "gem.h"


short
vsf_interior (short handle, short style)
{
	vdi_intin[0] = style;

	vdi_control[0] = 23;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * fill attribute
 */
