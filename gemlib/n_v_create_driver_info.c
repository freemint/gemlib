/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param driver_id device id (0-99)
 *
 *  @return A pointer to a DRV_INFO structur or 0L
 *
 *  @since NVDI 5.00
 *
 *
 *
 */

DRV_INFO *v_create_driver_info( short handle, short driver_id )
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 

	VDI_PARAMS(vdi_control, &driver_id, 0L, vdi_intout, 0L);
	
	VDI_TRAP (vdi_params, handle, 180, 0,1);

	if ( vdi_control[4] >= 2 )
		return vdi_intout_ptr(0, DRV_INFO *);

	return 0;
}
