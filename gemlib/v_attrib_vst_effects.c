
#include "gem.h"


int
vst_effects (int handle, int effects)
{
	vdi_intin[0] = effects;
	vdi_control[0] = 106;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * text attribute
 */
