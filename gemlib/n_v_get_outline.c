/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param handle Device handle
 *  @param index 
 *  @param x_offset 
 *  @param y_offset 
 *  @param pts 
 *  @param flags 
 *  @param max_pts 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_get_outline (short handle, short index, short x_offset, short y_offset,
               short *pts, char *flags, short max_pts)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[8];   
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
	
	vdi_intin    [0] = index;
	vdi_intin    [1] = max_pts;
	vdi_intin_ptr(2) = pts;
	vdi_intin_ptr(4) = flags;
	vdi_intin    [6] = x_offset;
	vdi_intin    [7] = y_offset;

	VDI_TRAP_ESC (vdi_params, handle, 243,1, 0,8);

	return vdi_intout[0];
}
