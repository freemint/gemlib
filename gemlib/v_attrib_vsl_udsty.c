
#include "gem.h"


void
vsl_udsty (int handle, int pat)
{
	vdi_intin[0] = pat;
	vdi_control[0] = 113;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * line attribute
 */
