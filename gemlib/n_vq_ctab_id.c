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
vq_ctab_id (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,2, 0,0);

	return vdi_intout_long(0);
}
