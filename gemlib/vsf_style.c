
#include "gem.h"


short
vsf_style (short handle, short style)
{
	vdi_intin[0] = style;
	vdi_control[0] = 24;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * fill attribute
 */
