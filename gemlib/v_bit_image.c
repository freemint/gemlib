
#include "gem.h"


void
v_bit_image (short handle, const char *filename, short aspect, short x_scale,
	     short y_scale, short h_align, short v_align, short *pxyarray)
{
	short n;

	vdi_intin[0] = aspect;
	vdi_intin[1] = x_scale;
	vdi_intin[2] = y_scale;
	vdi_intin[3] = h_align;
	vdi_intin[4] = v_align;
	n = vdi_str2array (filename, vdi_intin + 5);
	vdi_ptsin[0] = pxyarray[0];
	vdi_ptsin[1] = pxyarray[1];
	vdi_ptsin[2] = pxyarray[2];
	vdi_ptsin[3] = pxyarray[3];

	vdi_control[0] = 5;
	vdi_control[1] = 2;
	vdi_control[3] = n + 5;
	vdi_control[5] = 23;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * special graphic funkcion
 */
