
#include "gem.h"


int
vsf_perimeter (int handle, int vis)
{
	vdi_intin[0] = vis;
	vdi_control[0] = 104;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * fill attribute
 */
