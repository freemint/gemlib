/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param bg_color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vqr_bg_color (short handle, COLOR_ENTRY * bg_color)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[6]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L);
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 203,4, 0,0);

	*bg_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
