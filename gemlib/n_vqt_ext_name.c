
#include "gemx.h"


short
vqt_ext_name (short handle, short index, char *name, short *font_format, short *flags)
{
	vdi_intin[0] = index;
	vdi_intin[1] = 0;
	vdi_control[0] = 130;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 1;
	vdi_control[6] = handle;

	vdi (&vdi_params);

	vdi_array2str (vdi_intout + 1, name, 32);
	name[32] = vdi_intout[33];
	*flags = (vdi_intout[34] >> 8) & 0xff;
	*font_format = vdi_intout[34] & 0xff;
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 3.x or higher
 */
