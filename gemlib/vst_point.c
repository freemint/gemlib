
#include "gem.h"


short
vst_point (short handle, short point, short *charw, short *charh, short *cellw,
	   short *cellh)
{
	vdi_intin[0] = point;

	vdi_control[0] = 107;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	*charw = vdi_ptsout[0];
	*charh = vdi_ptsout[1];
	*cellw = vdi_ptsout[2];
	*cellh = vdi_ptsout[3];

	return vdi_intout[0];
}

/*
 * * text attribute
 */
