/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param vdi_index 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_ctab_vdi2idx (short handle, short vdi_index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, &vdi_index, 0L, vdi_intout, 0L);
#else
	vdi_intin[0] = vdi_index;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,4, 0,1);

	return vdi_intout[0];
}
