/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "gemx.h"

/** 
 *
 *  @param base_handle Device handle
 *  @param bitmap 
 *  @param color_flags 
 *  @param unit_flags 
 *  @param pixel_width 
 *  @param pixel_height 
 *
 *  @return 
 *
 *  @since NVDI 5 ?
 *
 *
 *
 */

short
v_open_bm (short base_handle, GCBITMAP * bitmap, short color_flags,
           short unit_flags, short pixel_width, short pixel_height)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[4];   
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
	
	vdi_intin[0] = color_flags;
	vdi_intin[1] = unit_flags;
	vdi_intin[2] = pixel_width;
	vdi_intin[3] = pixel_height;

	vdi_control_ptr(7) = bitmap;
	VDI_TRAP_ESC (vdi_params, base_handle, 100,3, 0,4);

	return vdi_control[6];
}
