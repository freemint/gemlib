/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab_length 
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
vq_ctab (short handle, long ctab_length, COLOR_TAB * ctab)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, (short*)&ctab_length, 0L, (short*)ctab, vdi_dummy);
#else
	*(long*)&vdi_intin[0] = ctab_length;
	vdi_params.intout = (short*)ctab;
#endif
	
	VDI_TRAP (vdi_params, handle, 206, 0,2);

#if !(USE_LOCAL_VDIPB)
	vdi_params.intout = vdi_intout;
#endif

	return (vdi_control[4] ? 1 : 0);
}
