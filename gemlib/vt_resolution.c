/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param xres 
 *  @param yres 
 *  @param xset 
 *  @param yset 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vt_resolution (short handle, short xres, short yres, short *xset, short *yset)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = xres;
	vdi_intin[1] = yres;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,81, 0,2);
	
	*xset = vdi_intout[0];
	*yset = vdi_intout[1];
}
