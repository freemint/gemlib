
#include "gem.h"


void
vst_error (int handle, int mode, short *errorvar)
{
	vdi_intin[0] = mode;
	*(short **) &vdi_intin[1] = (short *) &errorvar;
	vdi_control[0] = 245;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * text attribute
 */
