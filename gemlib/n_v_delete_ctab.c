/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_delete_ctab (short handle, COLOR_TAB * ctab)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, (short*)&ctab, 0L, vdi_intout, vdi_dummy);
#else
	vdi_intin_ptr(0) = ctab;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 206,9, 0,2);

	return vdi_intout[0];
}
