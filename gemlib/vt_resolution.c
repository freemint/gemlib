
#include "gem.h"


void
vt_resolution (short handle, short xres, short yres, short *xset, short *yset)
{
	vdi_intin[0] = xres;
	vdi_intin[1] = yres;
	vdi_control[0] = 5;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 81;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	*xset = vdi_intout[0];
	*yset = vdi_intout[1];
}

/*
 * * graphic table function
 */
