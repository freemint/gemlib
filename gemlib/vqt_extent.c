/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** If the selected font is a bitmap font, this function returns the minimal 
 *  bounding box of a string. If the selected font is a vector font, the character 
 *  widths (vqt_width()) will be added and the string (especially the leftmost and 
 *  the rightmost character) might exceed the returned rectangle.
 *
 *  @param handle Device handle
 *  @param str string
 *  @param extent coordinates of the rectangle
 *
 *  @since all VDI versions
 *
 *  The coordinates of the rectangle are given relative to a coordinate system, 
 *  where the extent rectangle touches both, the x and y axes, and the string is 
 *  in the first quadrant.
 *
 */

void
vqt_extent (short handle, const char *str, short extent[])
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		&vdi_intin[0],               /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		extent                       /* vdi_ptsout  */
	};
#endif
	register short n = vdi_str2array (str, vdi_intin);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsout = extent;
#endif
	
	VDI_TRAP (vdi_params, handle, 116, 0,n);

#if !(USE_LOCAL_VDIPB)
	vdi_params.ptsout = vdi_ptsout;
#endif
}
