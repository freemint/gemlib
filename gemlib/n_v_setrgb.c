
#include "gemx.h"


void
v_setrgb (short handle, short type, short r, short g, short b)
{
	vdi_intin[0] = r;
	vdi_intin[1] = g;
	vdi_intin[2] = b;

	vdi_control[0] = 138;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = type;
	vdi_control[6] = handle;
	vdi (&vdi_params);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
