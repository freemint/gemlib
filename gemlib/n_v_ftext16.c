
#include "gemx.h"


short vdi_wstrlen (const short *wstr);

void
v_ftext16 (short handle, short x, short y, const short *wstr)
{
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	vdi_control[0] = 241;
	vdi_control[1] = 1;
	vdi_control[3] = vdi_wstrlen (wstr);
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.intin = wstr;

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */