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
	short vdi_intin[2]; 
	short vdi_intout[1]; 

	*(DRV_INFO **) &vdi_intin[0] = drv_info;
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
	
	VDI_TRAP (vdi_params, handle, 181, 0,2);

	return vdi_intout[0];
}
