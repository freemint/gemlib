/*
 *  text attribute
 */

#include "gem_vdiP.h"


void
vst_alignment (short handle, short hin, short vin, short *hout, short *vout)
{
	vdi_intin[0] = hin;
	vdi_intin[1] = vin;

	VDI_TRAP (vdi_params, handle, 39, 0,2);

	*hout = vdi_intout[0];
	*vout = vdi_intout[1];
}
