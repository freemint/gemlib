#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This text function uses track and pair kerning and works with an internal 
 *  resolution of 1/65536 pixels to maintain accurate character placement.
 *
 *  @param handle Device handle
 *  @param x x-coordinate
 *  @param y y-coordinate
 *  @param str string
 *
 *  @since  NVDI 3.00
 *
 *  @note There is another variant of v_ftext() which allows your application to specifiy 
 *  the offset of each character relative to the previous one: v_ftext_offset()
 */

void
v_ftextn (short handle, short x, short y, const char *str, short num)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   
	short vdi_ptsin[2];   

	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy);
	
	num = vdi_str2array_n (str, vdi_intin, num);

	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;

	VDI_TRAP (vdi_params, handle, 241, 1,num);
}
