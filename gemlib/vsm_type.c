
#include "gem.h"


int
vsm_type (int handle, int symbol)
{
	vdi_intin[0] = symbol;
	vdi_control[0] = 18;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * marker attribute
 */
