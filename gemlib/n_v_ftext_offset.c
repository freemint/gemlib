
#include "gemx.h"


void
v_ftext_offset (short handle, short x, short y, const char *str, short *offset)
{
	short *ptr = vdi_intin;
	short i, len;

	len = i = vdi_str2array (str, vdi_intin);
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	ptr = &vdi_ptsin[2];
	for (i *= 2; i > 0; i--)
		*ptr++ = *offset++;

	vdi_control[0] = 241;
	vdi_control[1] = 1 + len;
	vdi_control[3] = len;
	vdi_control[6] = handle;

	vdi (&vdi_params);
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
