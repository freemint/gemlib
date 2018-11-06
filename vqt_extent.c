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
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short n = vdi_str2array_n (str, vdi_intin, VDI_INTINMAX);
	
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, extent );

	VDI_TRAP (vdi_params, handle, 116, 0,n);
}
