
#include "gemx.h"


short
v_opnprn (short aes_handle, PRN_SETTINGS *settings, short work_out[])
{
	register short i;

	vdi_intin[0] = settings->driver_id;
	
	for (i = 1; i < 10; i++)
		vdi_intin[i] = 1;
	
	vdi_intin[10] = 2;
	vdi_intin[11] = settings->size_id;

	*(char **) &vdi_intin[12] = settings->device;
	*(PRN_SETTINGS **) & vdi_intin[14] = settings;

	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	vdi_control[0] = 1;
	vdi_control[1] = 0;
	vdi_control[3] = 16;
	vdi_control[5] = 0;
	vdi_control[6] = aes_handle;
	
	vdi (&vdi_params);

	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
	
	return vdi_control[6];
}

/*
 * * NOTE: requires NVDI version 5.x or higher
 */
