
#include "gemx.h"


ITAB_REF
v_create_itab (int handle, COLOR_TAB * ctab, int bits)
{
	*(COLOR_TAB **) & vdi_intin[0] = ctab;
	vdi_intin[2] = bits;
	vdi_intin[3] = 0;
	vdi_intin[4] = 0;

	vdi_control[0] = 208;
	vdi_control[1] = 0;
	vdi_control[3] = 5;
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	return (*(ITAB_REF *) & vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
