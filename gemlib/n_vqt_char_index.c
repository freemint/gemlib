
#include "gemx.h"


int
vqt_char_index (int handle, int scr_index, int scr_mode, int dst_mode)
{
	vdi_intin[0] = scr_index;
	vdi_intin[1] = scr_mode;
	vdi_intin[2] = dst_mode;
	vdi_control[0] = 190;
	vdi_control[1] = 0;
	vdi_control[3] = 3;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);
	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 4.x or higher
 */
