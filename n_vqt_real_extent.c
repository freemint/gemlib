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
vqt_real_extent (short handle, short x, short y, const char *string, short extent[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_ptsin[2];   
	short n = vdi_str2array_n (string, vdi_intin, VDI_INTINMAX);

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, extent);

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,n);
}
