/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param mode 
 *  @param errorvar 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
vst_error (short handle, short mode, short *errorvar)
{
#if USE_LOCAL_VDIPB
	/* todo (doc wanted) */
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	short vdi_intout[VDI_INTOUTMAX]; 
	short vdi_ptsout[VDI_PTSOUTMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		&vdi_ptsout[0]               /* vdi_ptsout  */
	};
#endif
	
	vdi_intin    [0] = mode;
	vdi_intin_ptr(1) = errorvar;
	
	VDI_TRAP (vdi_params, handle, 245, 0,3);
}
