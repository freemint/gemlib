
#include "gem.h"


void
vsp_film (int handle, int index, int lightness)
{
	vdi_intin[0] = index;
	vdi_intin[1] = lightness;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 91;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * polaroid function
 */
