/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function is only available if you use NVDI.
 *  It returns the bounding box (eventually a quadrilateral, not a rectangle) for 
 *  text output at \p x, \p y. This function considers all text effects, rotation, 
 *  skewing, pair kerning, track kerning, characters which are extending beyond the 
 *  em square, horizontal and vertical alignment.
 *
 *  @param handle Device handle
 *  @param x x-coordinate
 *  @param y y-coordinate
 *  @param string string
 *  @param extent coordinates of the bounding box
 *
 *  @since NVDI 3.00
 *
 *
 *
 */

void
vqt_real_extent (short handle, short x, short y, char *string, short extent[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_ptsin[2];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		&vdi_ptsin[0],               /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		extent                       /* vdi_ptsout  */
	};
#endif
	register short n = vdi_str2array (string, vdi_intin);
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsout = extent;
#endif

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,n);
	
#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsout = vdi_ptsout;
#endif
}
