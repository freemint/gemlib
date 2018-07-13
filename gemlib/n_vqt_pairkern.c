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
 *  @param x x-adjustment in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] x may be NULL
 *  @param y y-adjustment in 1/65536 pixels \n
 *         [option CHECK_NULLPTR] y may be NULL
 *
 *  @since NVDI 3.00
 *
 */

void
vqt_pairkern (short handle, short ch1, short ch2, long *x, long *y)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[4]; 

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, vdi_dummy);
	
	vdi_intin[0] = ch1;
	vdi_intin[1] = ch2;
	
	VDI_TRAP (vdi_params, handle, 235, 0,2);
	
#if CHECK_NULLPTR
	if (x)
#endif
	{
		*x = vdi_intout_long(0);
	}
#if CHECK_NULLPTR
	if (y)
#endif
	{
		*y = vdi_intout_long(2);
	}
}
