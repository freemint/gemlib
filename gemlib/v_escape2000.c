
#include "gem.h"


void
v_escape2000 (int handle, int times)
{
	vdi_intin[0] = times;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 2000;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * special function
 */
