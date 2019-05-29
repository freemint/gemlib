#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param aes_handle Device handle
 *  @param settings pointer to printer settings
 *  @param work_out pointer to work_out[57]
 *
 *  @return device handle
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_opnprn (short aes_handle, PRN_SETTINGS *settings, short work_out[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[12 + 2 * N_PTRINTS];
	short i;

	VDI_PARAMS(vdi_control, vdi_intin, 0L, &work_out[0], &work_out[45] );
	
	vdi_intin[0] = settings->driver_id;
	for (i = 1; i < 10; vdi_intin[i++] = 1);
	vdi_intin    [10] = 2;
	vdi_intin    [11] = settings->size_id;
	vdi_intin_ptr(12, char *) = settings->device;
	vdi_intin_ptr(12 + N_PTRINTS, PRN_SETTINGS *) = settings;

	VDI_TRAP (vdi_params, aes_handle, 1, 0, 12 + 2 * N_PTRINTS);
	
	return vdi_control[6];
}
