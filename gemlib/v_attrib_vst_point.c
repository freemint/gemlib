
#include "gem.h"


int
vst_point (int handle, int point, int *charw, int *charh, int *cellw,
	   int *cellh)
{
	vdi_intin[0] = point;
	vdi_control[0] = 107;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*charw = vdi_ptsout[0];
	*charh = vdi_ptsout[1];
	*cellw = vdi_ptsout[2];
	*cellh = vdi_ptsout[3];
	return (int) vdi_intout[0];
}

/*
 * * text attribute
 */
