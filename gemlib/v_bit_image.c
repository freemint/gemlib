/*
 *   special graphic funkcion
 */

#include "gem_vdiP.h"


void
v_bit_image (short handle, const char *filename, short aspect, short x_scale,
             short y_scale, short h_align, short v_align, short *pxy)
{
	register short n = 5 + vdi_str2array (filename, vdi_intin + 5);

	vdi_params.ptsin = pxy;
	
	vdi_intin[0] = aspect;
	vdi_intin[1] = x_scale;
	vdi_intin[2] = y_scale;
	vdi_intin[3] = h_align;
	vdi_intin[4] = v_align;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,23, 2,n);

	vdi_params.ptsin = vdi_ptsin;
}
