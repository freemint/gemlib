
#include "gem.h"


short
vst_rotation (short handle, short ang)
{
	vdi_intin[0] = ang;
	vdi_control[0] = 13;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * text attribute
 */
