/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_point (short handle, short point,
           short *charw, short *charh, short *cellw, short *cellh)
{
	vdi_intin[0] = point;

	VDI_TRAP (vdi_params, handle, 107, 0,1);

	*charw = vdi_ptsout[0];
	*charh = vdi_ptsout[1];
	*cellw = vdi_ptsout[2];
	*cellh = vdi_ptsout[3];

	return vdi_intout[0];
}
