#include "gem_vdiP.h"
#include "mt_gemx.h"

/** As well as vqt_extent() this function adds the character widths of a string, but 
 *  this function takes track and pair kerning into account and works with a resolution 
 *  of 1/65536 pixels. Text effects like skewing (vst_skew()) and characters which are 
 *  extending beyond the em square are ignored.
 *
 *  @param handle Device handle
 *  @param str string
 *  @param extent extent[0..7] : coordinates of the rectangle
 * 
 *  @since NVDI 3.00
 *
 *  @note
 *  If the text is rotated by 90, 180 or 270 degrees, this function works as senseless 
 *  as vqt_extent(): It changes the reference point of the coordinate system. In all 
 *  other cases it works as you would expect it.
 *  
 *  @note
 *  This function does not return the bounding box of the string. It adds only the 
 *  advance widths of the characters. You should use this function to determine the 
 *  position of the text cursor.
 *  If you would like to use it to determine the maximum size of the redraw area 
 *  you should add the maximum character width to the leftmost and rightmost coordinates 
 *  of the rectangle (if the text is skewed you should also add the skewing offset).
 *  To determine a more exact bounding box you should call vqt_real_extent().
 *
 */

void
vqt_f_extentn (short handle, const char *str, short num, short extent[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, extent);

	num = vdi_str2array_n (str, vdi_intin, num);

	VDI_TRAP (vdi_params, handle, 240, 0,num);
}
