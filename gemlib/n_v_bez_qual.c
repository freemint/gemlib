/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** specifies the  quality and accuracy of the bezier curves. You can 
 *  select the quality in a range between 0 and 100 per cent. 
 *
 *  @param handle Device handle
 *  @param percent requested bezier quality
 *  @param actual realized bezier quality
 *
 *  @since since NVDI 2.10
 *
 *
 *
 */

void
v_bez_qual (short handle, short percent, short *actual)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		actual,                      /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_intin[0] = 32;
	vdi_intin[1] = 1;
	vdi_intin[2] = percent;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,99, 0,3);
	
#if !(USE_LOCAL_VDIPB)
	*actual = vdi_intout[0];
#endif
}
