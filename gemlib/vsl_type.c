
#include "gem.h"


short
vsl_type (short handle, short style)
{
	vdi_intin[0] = style;
	vdi_control[0] = 15;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_intout[0];
}

/*
 * * line attribute
 */
