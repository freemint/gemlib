/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vq_margins (short handle, short *top_margin, short *bottom_margin,
            short *left_margin, short *right_margin, short *hdpi, short *vdpi)
{
	vdi_intout[0] = 0;

	VDI_TRAP_ESC (vdi_params, handle, 5,2100, 0,0);

	*top_margin    = vdi_intout[1];
	*bottom_margin = vdi_intout[2];
	*left_margin   = vdi_intout[3];
	*right_margin  = vdi_intout[4];
	*hdpi          = vdi_intout[5];
	*vdpi          = vdi_intout[6];

	return vdi_intout[0];
}
