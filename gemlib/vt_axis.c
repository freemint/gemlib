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
 *  @return 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vt_axis (short handle, short xres, short yres, short *xset, short *yset)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];   
	short vdi_intout[2]; 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_intout, 0L );
#endif
	
	vdi_intin[0] = xres;
	vdi_intin[1] = yres;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,82, 0,2);
	
	*xset = vdi_intout[0];
	*yset = vdi_intout[1];
}
