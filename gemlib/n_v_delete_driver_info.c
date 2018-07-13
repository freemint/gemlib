/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param drv_info Pointer from v_create_driver_info
 *
 *  @return
 *
 *  @since NVDI 5.00
 *
 *
 *
 */

short v_delete_driver_info( short handle, DRV_INFO *drv_info )
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[N_PTRINTS];
	short vdi_intout[1];
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);

	vdi_intin_ptr(0, DRV_INFO *) = drv_info;
		
	VDI_TRAP (vdi_params, handle, 181, 0, N_PTRINTS);

	return vdi_intout[0];
}
