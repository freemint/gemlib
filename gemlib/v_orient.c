/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function is used for switching between portrait and landscape 
 *  output of a page. If \p orientation is -1, the current orientation is returned.
 *
 *  @param handle Device handle
 *  @param orientation requested orientation :
 *         - (-1) just return orientation
 *         - (0)  set to portrait
 *         - (1)  set to landscape
 *
 *  @return realized orientation as follow:
 *         - (-1) error (not enough memory) => close the driver
 *         - (0)  portrait
 *         - (1)  landscape
 *
 *  @since depends on the driver. If the driver doesn't support this fonction,
 *         1 will be returned whatever orientation is.
 *
 *
 *  If there is not enough memory to change the orientation, v_orient returns -1.
 *  If that is the case you have to close the driver via v_clswk().
 *  
 *
 */

short
v_orient (short handle, short orientation)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&orientation,                /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		&vdi_intout[0],              /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#else
	vdi_intin[0] = orientation;
#endif
		
	VDI_TRAP_ESC (vdi_params, handle, 5,27, 0,1);
	
	if (vdi_control[4])  /* function supported */
		return vdi_intout[0];
	
	/* function not supported by the driver */
	return 1;
}
