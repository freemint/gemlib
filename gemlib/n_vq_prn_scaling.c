/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

long
vq_prn_scaling (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	static short vdi_intin[2] = {-1,-1};   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#else
	vdi_intin[0] = -1;
	vdi_intin[1] = -1;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,39, 0,2);

	return (vdi_control[4] == 2 ? vdi_intout_long(0) : -1L);
}
