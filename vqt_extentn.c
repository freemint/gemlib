#include "gem_vdiP.h"

/** see vqt_extent()
 *
 *  @param handle Device handle
 *  @param str string
 *  @param num length of the string
 *  @param extent coordinates of the rectangle
 *
 */

void
vqt_extentn (short handle, const char *str, short num, short extent[])
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[VDI_INTINMAX];   

	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, extent );
	num = vdi_str2array_n (str, vdi_intin, num);
	
	VDI_TRAP (vdi_params, handle, 116, 0,num);
}
