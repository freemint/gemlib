
#include "gem.h"


void
vst_scratch (short handle, short mode)
{
	vdi_intin[0] = mode;

	vdi_control[0] = 244;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);
}

/*
 * * text attribute
 */
