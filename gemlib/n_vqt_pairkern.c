/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

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
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = ch1;
	vdi_intin[1] = ch2;
	
	VDI_TRAP (vdi_params, handle, 235, 0,2);
	
	*x = *(long*)&vdi_intout[0];
	*y = *(long*)&vdi_intout[2];
}
