/*
 *  text attribute
 */

#include "gem_vdiP.h"


short
vst_height (short handle, short height,
            short *charw, short *charh, short *cellw, short *cellh)
{
	vdi_ptsin[0] = 0;
	vdi_ptsin[1] = height;

	VDI_TRAP (vdi_params, handle, 12, 1,0);

	*charw = vdi_ptsout[0];
	*charh = vdi_ptsout[1];
	*cellw = vdi_ptsout[2];
	*cellh = vdi_ptsout[3];

	return vdi_intout[0];
}
