/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gemx.h"


void
vqt_f_extent16 (short handle, const short *wstr, short extent[])
{
	register short i;

	vdi_control[0] = 240;
	vdi_control[1] = 0;
	vdi_control[3] = vdi_wstrlen (wstr);
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.intin = wstr;

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;

	for (i = 0; i < 8; i++)
		extent[i] = vdi_ptsout[i];
}
