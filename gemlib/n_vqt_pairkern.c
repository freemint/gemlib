/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function returns the adjustment vector for pair kerning
 *
 *  @param handle Device handle
 *  @param ch1 first character
 *  @param ch2 following character
 *  @param x x-adjustment in 1/65536 pixels
 *  @param y y-adjustment in 1/65536 pixels
 *
 *  @since NVDI 3.00
 *
 */

void
vqt_pairkern (short handle, short ch1, short ch2, long *x, long *y)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[4]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L);
#endif
	
	vdi_intin[0] = ch1;
	vdi_intin[1] = ch2;
	
	VDI_TRAP (vdi_params, handle, 235, 0,2);
	
	*x = *(long*)&vdi_intout[0];
	*y = *(long*)&vdi_intout[2];
}
