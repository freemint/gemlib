/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns the adjustment vector per character for track kerning
 *
 *  @param handle Device handle
 *  @param x x-adjustment in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] x may be NULL
 *  @param y y-adjustment in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] y may be NULL
 *
 *  @since NVDI 3.00
 *
 */

void
vqt_trackkern (short handle, long *x, long *y)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[4]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy);
	
	VDI_TRAP_00 (vdi_params, handle, 234);
	
#if CHECK_NULLPTR
	if (x)
#endif
	*x = *(long*)&vdi_intout[0];
#if CHECK_NULLPTR
	if (y)
#endif
	*y = *(long*)&vdi_intout[2];
}
