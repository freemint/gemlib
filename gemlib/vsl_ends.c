
#include "gem.h"


void
vsl_ends (short handle, short begstyle, short endstyle)
{
	vdi_intin[0] = begstyle;
	vdi_intin[1] = endstyle;
	vdi_control[0] = 108;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * line attribute
 */
