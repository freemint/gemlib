/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param color_space 
 *  @param fg_color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vsl_fg_color (short handle, long color_space, COLOR_ENTRY * fg_color)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[6];   
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	*(long*)       &vdi_intin[0] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[2] = *fg_color;

	VDI_TRAP_ESC (vdi_params, handle, 200,2, 0,6);

	return vdi_intout[0];
}
