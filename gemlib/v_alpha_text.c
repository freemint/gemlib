/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param str 
 *
 *  @since 
 *
 *  @sa
 *
 *
 *
 */

void
v_alpha_text (short handle, const char *str)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_intout[5]; /* from TOS.HYP */
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	register short n = vdi_str2array (str, vdi_intin);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,25, 0,n);
}
