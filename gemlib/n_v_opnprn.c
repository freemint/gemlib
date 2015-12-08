/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param aes_handle Device handle
 *  @param settings 
 *  @param work_out 
 *
 *  @return 
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
	short vdi_intin[16];   
	short i;

	VDI_PARAMS(vdi_control, vdi_intin, 0L, &work_out[0], &work_out[45] );
	
	vdi_intin[0] = settings->driver_id;
	for (i = 1; i < 10; vdi_intin[i++] = 1);
	vdi_intin    [10] = 2;
	vdi_intin    [11] = settings->size_id;
	vdi_intin_ptr(12) = settings->device;
	vdi_intin_ptr(14) = settings;

	VDI_TRAP (vdi_params, aes_handle, 1, 0,16);
	
	return vdi_control[6];
}
