/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function report back, if vs_calibrate() exists and if calibration is 
 *  switched on.
 *
 *  @param handle Device handle
 *  @param flag calibration aus (0) or ein (1)
 *
 *  @return O if vs_calibrate() is not supported by the driver, any other value
 *          if vs_calibrate() is supported by the driver.
 *
 *  @since depends on the driver
 *
 */

short
vq_calibrate (short handle, short *flag)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		flag,                        /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,77, 0,0);
	
#if !(USE_LOCAL_VDIPB)
	*flag = vdi_intout[0];
#endif
	
	return vdi_control[4];
}
