
#include "gemx.h"


short
vs_ctab (short handle, COLOR_TAB * ctab)
{
	vdi_params.intin = (short *) ctab;

	vdi_control[0] = 205;
	vdi_control[1] = 0;
	vdi_control[3] = (short) (ctab->length / 2);
	vdi_control[5] = 0;
	vdi_control[6] = handle;
	vdi (&vdi_params);

	vdi_params.intin = vdi_intin;

	return (vdi_intout[0]);
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
