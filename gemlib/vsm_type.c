
#include "gem.h"


short
vsm_type (short handle, short symbol)
{
	vdi_intin[0] = symbol;

	vdi_control[0] = 18;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * marker attribute
 */
