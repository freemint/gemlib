/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param ctab 
 *  @param bits 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

ITAB_REF
v_create_itab (short handle, COLOR_TAB * ctab, short bits)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[5];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	vdi_intin_ptr(0) = ctab;
	vdi_intin    [2] = bits;
	vdi_intin    [3] = 0;
	vdi_intin    [4] = 0;

	VDI_TRAP (vdi_params, handle, 208, 0,5);

	return *(ITAB_REF*)&vdi_intout[0];
}
