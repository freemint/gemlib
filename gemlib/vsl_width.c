
#include "gem.h"


short
vsl_width (short handle, short width)
{
	vdi_ptsin[0] = width;
	vdi_ptsin[1] = 0;
	vdi_control[0] = 16;
	vdi_control[1] = 1;
	vdi_control[3] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return (int) vdi_ptsout[0];
}

/*
 * * line attribute
 */
