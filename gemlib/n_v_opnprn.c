/*
 *   NOTE: requires NVDI version 5.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
v_opnprn (short aes_handle, PRN_SETTINGS *settings, short work_out[])
{
	register short i;

	vdi_intin[0] = settings->driver_id;
	for (i = 1; i < 10; vdi_intin[i++] = 1)
	vdi_intin    [10] = 2;
	vdi_intin    [11] = settings->size_id;
	vdi_intin_ptr(12) = settings->device;
	vdi_intin_ptr(14) = settings;

	vdi_params.intout = &work_out[0];
	vdi_params.ptsout = &work_out[45];

	VDI_TRAP (vdi_params, aes_handle, 1, 0,16);

	vdi_params.intout = &vdi_intout[0];
	vdi_params.ptsout = &vdi_ptsout[0];
	
	return vdi_control[6];
}
