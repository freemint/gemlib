/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param hilite_color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_hilite_color (short handle, COLOR_ENTRY * hilite_color)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[VDI_INTOUTMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L);
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 209);

	*hilite_color = *(COLOR_ENTRY*)&vdi_intout[2];
	
	return vdi_intout_long(0);
}
