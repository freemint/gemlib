
#include "gemx.h"


short
v_delete_ctab (short handle, COLOR_TAB * ctab)
{
	*(COLOR_TAB **) & vdi_intin[0] = ctab;

	vdi_control[0] = 206;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 9;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
