/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function displays a string. The string starts at the current cursor 
 *  position.
 *
 *  @param handle Device handle
 *  @param str 
 *
 *  @since all VDI versions
 *
 */

void
v_curtext (short handle, const char *str)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L, 						 /* vdi_ptsin	*/
		0L, 						 /* vdi_intout  */
		0L							 /* vdi_ptsout  */
	};
#endif
	register short n = vdi_str2array (str, vdi_intin);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,12, 0,n);
}
