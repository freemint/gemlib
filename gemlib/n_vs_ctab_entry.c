/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *  @param color_space 
 *  @param color 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
vs_ctab_entry (short handle, short index, long color_space, COLOR_ENTRY * color)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[7];   
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
	
	vdi_intin                [0] = index;
	*(long*)       &vdi_intin[1] = color_space;
	*(COLOR_ENTRY*)&vdi_intin[3] = *color;

	VDI_TRAP_ESC (vdi_params, handle, 205,1, 0,7);

	return vdi_intout[0];
}
