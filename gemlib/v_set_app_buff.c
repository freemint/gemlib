/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param buf_p 
 *  @param size 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
v_set_app_buff (short handle, void *buf_p, short size)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[1 + N_PTRINTS];

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
	
	vdi_intin_ptr(0, void *) = buf_p;
	vdi_intin    [N_PTRINTS] = size;
	
	VDI_TRAP_ESC (vdi_params, handle, -1,6, 0, 1 + N_PTRINTS);
}
