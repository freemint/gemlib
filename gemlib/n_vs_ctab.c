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
vs_ctab (short handle, COLOR_TAB * ctab)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, (short *) ctab, 0L, vdi_intout, vdi_dummy );
#else
	vdi_params.intin = (short *) ctab;
#endif
	
	VDI_TRAP (vdi_params, handle, 205, 0,(short)(ctab->length /2));

#if !(USE_LOCAL_VDIPB)
	vdi_params.intin = vdi_intin;
#endif

	return (vdi_intout[0]);
}
