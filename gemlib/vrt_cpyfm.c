/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function expands a monochrome raster (one plane) considering the 
 *  foreground and background color and copies the raster onto the destination 
 *  raster using the specified writing mode.
 *
 *  @param handle Device handle
 *  @param mode writing mode
 *  @param pxy coordinates
 *         - xyarr[0..3]: coordinates of the source rectangle
 *         - xyarr[4..7]: coordinates of the destination rectangle
 *  @param src pointer to the source MFDB
 *  @param dst pointer to the destination MFDB
 *  @param color 
 *         - color[0] : color index for "black" points
 *         - color[1] : color index for "white" points
 *
 *  @since all VDI versions
 *
 *  If the screen is the destination raster, fd_addr should be zero!
 *
 *  Note:\n
 *  Usually vrt_cpyfm() ignores the height and width of the destination rectangle 
 *  and uses the size of the source. If you want to scale a bitmap, you have to 
 *  set the most significant bit in the transfer mode (wr_mode | 0x8000). In this
 *  case vrt_cpyfm() scales the bitmap according to the size of the destination 
 *  rectangle. Wheter the driver is able to scale or not is returned by vq_extnd() 
 *  in work_out[30] (you are only allowed to set the upper bit of the mode if it 
 *  is able to).
 *  
 */

void
vrt_cpyfm (short handle, short mode, short pxy[], MFDB *src, MFDB *dst,
           short color[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[3];   

	VDI_PARAMS(vdi_control, vdi_intin, pxy, vdi_dummy, vdi_dummy );
	
	vdi_intin[0]            = mode;
	*((long*)&vdi_intin[1]) = *(long*)color;
	vdi_control_ptr(7)      = src;
	vdi_control_ptr(9)      = dst;

	VDI_TRAP (vdi_params, handle, 121, 4,3);
}
