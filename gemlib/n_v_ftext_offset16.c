/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gemx.h"


void
v_ftext_offset16 (short handle, short x, short y, const short *wstr,
		  short *offset)
{
	short *ptr;
	short i, len;

	len = i = vdi_wstrlen (wstr);

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	ptr = &vdi_ptsin[2];
	for (i *= 2; i > 0; i--)
		*ptr++ = *offset++;

	vdi_control[0] = 241;
	vdi_control[1] = 1 + len;
	vdi_control[3] = len;
	vdi_control[5] = 0;
	vdi_control[6] = handle;

	vdi_params.intin = wstr;

	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;
}
