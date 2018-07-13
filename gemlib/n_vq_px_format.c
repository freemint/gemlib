/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param px_format  \n
 *         [option CHECK_NULLPTR] px_format may be NULL
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_px_format (short handle, unsigned long *px_format)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[4]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 204,3, 0,0);

#if CHECK_NULLPTR
	if (px_format)
#endif
	{
		*px_format = vdi_intout_long(2);
	}
	
	return vdi_intout_long(0);
}
