/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

unsigned long
v_ctab_idx2value (short handle, short index)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, &index, 0L, vdi_intout, 0L);
#else
	vdi_intin[0] = index;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,5, 0,1);

	return *(unsigned long *)&vdi_intout[0];
}
