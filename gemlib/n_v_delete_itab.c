
#include "gemx.h"


short
v_delete_itab (short handle, ITAB_REF itab)
{
	*(ITAB_REF *) & vdi_intin[0] = itab;

	vdi_control[0] = 208;
	vdi_control[1] = 0;
	vdi_control[3] = 2;
	vdi_control[5] = 1;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return vdi_intout[0];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
