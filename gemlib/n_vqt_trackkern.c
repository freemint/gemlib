/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns the adjustment vector per character for track kerning
 *
 *  @param handle Device handle
 *  @param x x-adjustment in 1/65536 pixels
 *  @param y y-adjustment in 1/65536 pixels
 *
 *  @since NVDI 3.00
 *
 */

void
vqt_trackkern (short handle, long *x, long *y)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[4]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, 0L);
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 234);
	
	*x = *(long*)&vdi_intout[0];
	*y = *(long*)&vdi_intout[2];
}
