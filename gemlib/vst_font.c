
#include "gem.h"


short
vst_font (short handle, short font)
{
	vdi_intin[0] = font;

	vdi_control[0] = 21;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * text attribute
 */
