
#include "gem.h"


short
vqt_width (short handle, short chr, short *cw, short *ldelta, short *rdelta)
{
	vdi_intin[0] = chr;
	vdi_control[0] = 117;
	vdi_control[1] = 0;
	vdi_control[3] = 1;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*cw = vdi_ptsout[0];
	*ldelta = vdi_ptsout[2];
	*rdelta = vdi_ptsout[4];
	return vdi_intout[0];
}
