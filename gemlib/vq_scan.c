
#include "gem.h"


void
vq_scan (short handle, short *g_slice, short *g_page, short *a_slice, short *a_page,
	 short *div_fac)
{
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 0;
	vdi_control[5] = 24;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*g_slice = vdi_intout[0];
	*g_page = vdi_intout[1];
	*a_slice = vdi_intout[2];
	*a_page = vdi_intout[3];
	*div_fac = vdi_intout[4];
}

/*
 * * special graphic funkcion
 */
